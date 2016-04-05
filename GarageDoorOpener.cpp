#include "GarageDoorOpener.h"

bool TRANSITIONED = false;
bool SETMOTORDOWN = false;
bool SETMOTORUP = false;
bool SETBEAM = false;
bool MUTEX = false;
bool INTERRUPT = false;
bool BUTTON = false;
bool OVERCURRENT = false;
bool RESET = false;
bool stopGDO = false;
bool SIMULATION = SOFTWARE;


// GarageDoorOpener constructor
GarageDoorOpener::GarageDoorOpener()
{
	// Initialize counter
	count = 0;
	hwFlag = false;

    //myStateContext = new StateContext(&ClosedState, CLOSED);
    myStateContext = new StateContext(this, CLOSED);

    // Configure QNX DAIO Port B as Output Port by default
    // Configure QNX DAIO Port C as Input Port by default
    int success = setHWConns();
    if(success == -1)
    {
		 return;
    }
    resetHWSimulator();

    // create the inputscanner thread
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);		// initialize thread attributes structure
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&GDOThreadID, &threadAttr, &GarageDoorOpener::DoorThread, this);
}

// GarageDoorOpener destructor
GarageDoorOpener::~GarageDoorOpener()
{
    pthread_join(GDOThreadID, NULL);
}


// Thread to be called when Door is opening or closing
void* GarageDoorOpener::DoorThread(void* param)
{
    int privity_err;
    // Give this thread root permissions to access the hardware
    privity_err = ThreadCtl(_NTO_TCTL_IO, NULL);
    if (privity_err == -1) {
        std::cout <<"can't get root permissions" << std::endl;
        return NULL;
    }

	while(!stopGDO)
	{
		if(::RESET == true)
		{
			((GarageDoorOpener*)param)->count = 0;
			((GarageDoorOpener*)param)->hwFlag = false;
			::TRANSITIONED = false;
			((GarageDoorOpener*)param)->myStateContext->transition('R');
			::RESET = false;
		}

		//Printing the countdown if the door is moving
		if(::SETMOTORDOWN == true || ::SETMOTORUP == true)
		{
			if(::SETMOTORDOWN == true)
			{
				((GarageDoorOpener*)param)->count--;
				
				if(::SIMULATION == HARDWARE)
				{
					if(!((GarageDoorOpener*)param)->hwFlag)
					{
						// Decrement HW Counter & Turn on IR Beam
						out8(((GarageDoorOpener*)param)->daio_portB_handle, 0x1C);
						((GarageDoorOpener*)param)->hwFlag = true;
					}
				}

				std::cout << "DOOR IS MOVING DOWN: "
						  << ((GarageDoorOpener*)param)->count << std::endl;
			}
			
			else if(::SETMOTORUP == true)
			{
				((GarageDoorOpener*)param)->count++;
				
				if(::SIMULATION == HARDWARE)
				{
					if(!((GarageDoorOpener*)param)->hwFlag)
					{
						// Increment HW Counter & Turn off IR beam
						out8(((GarageDoorOpener*)param)->daio_portB_handle, 0x12);
						((GarageDoorOpener*)param)->hwFlag = true;
					}
				}

				std::cout << "DOOR IS MOVING UP: "
						  << ((GarageDoorOpener*)param)->count << std::endl;
			}
		}

		if(::SIMULATION == SOFTWARE)
		{
			//Garage door has fully closed or opened
			if((((GarageDoorOpener*)param)->count == 0 && ::SETMOTORDOWN == true) ||
					(((GarageDoorOpener*)param)->count == 10 && ::SETMOTORUP == true))
			{
				((GarageDoorOpener*)param)->myStateContext->transition('F');
				::TRANSITIONED = true;
			}
		}
		else if(::SIMULATION == HARDWARE)
		{
			// Read C0 and C1
			int val = in8(((GarageDoorOpener*)param)->daio_portC_handle) & 0x03;

			//Garage door has fully closed or opened
			if((val == 2 && ::SETMOTORDOWN == true) ||
					(val == 1 && ::SETMOTORUP == true))
			{
				// Stop driving the HW counter and & turn off the IR beam
				out8(((GarageDoorOpener*)param)->daio_portB_handle, 0x10);
				((GarageDoorOpener*)param)->hwFlag = false;
				((GarageDoorOpener*)param)->myStateContext->transition('F');
				::TRANSITIONED = true;
			}			
		}


		//Looking for messages from inputscanner
		if(::MUTEX == false)
		{
			::MUTEX = true;
			if(::OVERCURRENT == true)
			{
				((GarageDoorOpener*)param)->myStateContext->transition('O');
				::OVERCURRENT = false;
			}
			if(::BUTTON == true)
			{
				((GarageDoorOpener*)param)->myStateContext->transition('P');
				::BUTTON = false;
			}
			if(::INTERRUPT == true && ::SETBEAM == true)
			{
				((GarageDoorOpener*)param)->myStateContext->transition('I');
				::INTERRUPT = false;
				::SETBEAM = false;
			}

			::MUTEX = false;
		}
		
		sleep(1);
	}

	return 0;
}


int GarageDoorOpener::setHWConns(void)
{
    int privity_err;
    /* Give this thread root permissions to access the hardware */
    privity_err = ThreadCtl(_NTO_TCTL_IO, NULL);
    if (privity_err == -1) {
        std::cout <<"can't get root permissions" << std::endl;
        return -1;
    }

    // Get a handle to the DAIO port's registers
    daio_ctrl_handle    = mmap_device_io(PORT_LENGTH, BASE_ADDRESS + DAIO_CONTROLREG_ADDRESS);
    daio_portB_handle   = mmap_device_io(PORT_LENGTH, BASE_ADDRESS + DAIO_PORTB_ADDRESS);
    daio_portC_handle   = mmap_device_io(PORT_LENGTH, BASE_ADDRESS + DAIO_PORTC_ADDRESS);

    // Configure DAIO Port B as Output Port by default
    // Configure DAIO Port C as Input Port by default
    // -- output port - 0
    // -- input port - 1
    // Control Reg Bits --> DIOCTR | X | X | DIRA | DIRCH | X | DIRB | DIRCL
    daio_ctrl_handle = mmap_device_io(PORT_LENGTH, BASE_ADDRESS + DAIO_CONTROLREG_ADDRESS);
    int val = in8(daio_ctrl_handle);
    out8(daio_ctrl_handle, (0x89 | val)); // Set PORT C -> 0b[1]000[1]00[1]
    val = in8(daio_ctrl_handle); 
    out8(daio_ctrl_handle, (0xFD & val)); // Set PORT B -> 0b111111[0]1
    return 1;
}


bool GarageDoorOpener::resetHWSimulator()
{
	out8(daio_portB_handle, 0x00);
	sleep(0.1);
	out8(daio_portB_handle, 0x10);
	return true;
}
