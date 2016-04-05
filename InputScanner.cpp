#include "InputScanner.h"


InputScanner::InputScanner()
{
	int privity_err;
	/* Give this thread root permissions to access the hardware */
	privity_err = ThreadCtl(_NTO_TCTL_IO, NULL);
	if (privity_err == -1) {
		std::cout <<"can't get root permissions" << std::endl;
		return;
	}

    // Get a handle to the DAIO port's registers
    daio_ctrl_handle    = mmap_device_io(PORT_LENGTH, BASE_ADDRESS + DAIO_CONTROLREG_ADDRESS);
    daio_portA_handle   = mmap_device_io(PORT_LENGTH, BASE_ADDRESS + DAIO_PORTA_ADDRESS);

    // Configure DAIO Port A as Input Port by default
    // -- output port - 0
    // -- input port - 1
    daio_ctrl_handle = mmap_device_io(PORT_LENGTH, BASE_ADDRESS + DAIO_CONTROLREG_ADDRESS);
    int val = in8(daio_ctrl_handle);
    out8(daio_ctrl_handle, 0x80 | val);

	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);		// initialize thread attributes structure
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&inputScannerThreadID, &threadAttr, &InputScanner::InputScannerThread, this);

}

InputScanner::~InputScanner()
{
    pthread_join(inputScannerThreadID, NULL);
}

void* InputScanner::InputScannerThread(void* arg)
{
    int privity_err;
    // Give this thread root permissions to access the hardware
    privity_err = ThreadCtl(_NTO_TCTL_IO, NULL);
    if (privity_err == -1) {
        std::cout <<"can't get root permissions" << std::endl;
        return NULL;
    }


    char userChoice = 'x';
    char simulation = 's';

	// Start the scanning
	std::cout << "\nEnter your choice: [ ";
	std::cout << "'h' : to indicate Hardware Simulation | "
			  << "'s' : to indicate Software Simulation ] : ";
	std::cin >> simulation;
	if (tolower(simulation) == 'h')
		::SIMULATION = HARDWARE;
	else if (tolower(simulation) == 's')
		::SIMULATION = SOFTWARE;

	do{
		if(::SIMULATION == SOFTWARE)
		{
			std::cout << "'m' : to indicate motor overcurrent | "
					  << "'i' : to indicate infrared beam interruption | "
					  << "'r' : to indicate remote button press | "
					  << "'x' : to reset | "
					  << "'e' : to stop GDO ] : ";
			std::cin >> userChoice;

			switch(tolower(userChoice))
			{
				case 'm': // motor overcurrent
					((InputScanner*)arg)->alertOvercurrent(); // set the shared variable
					break;

				case 'i': // infrared beam interruption
					((InputScanner*)arg)->alertbeam(); // set the shared variable
					break;

				case 'r': // remote button press
					sleep(1); // simulate a 1 second press
					((InputScanner*)arg)->alertbutton(); // set the shared variable
					break;

				case 'x': // reset simulator
					((InputScanner*)arg)->resetSim(); // set the shared variable
					break;

				case 'e': // reset simulator
					stopGDO = true; // set the shared variable
					break;

				default:
					std::cout << "\nInvalid option. Try again" << std::endl << std::endl;
			}
		}

		else if(::SIMULATION == HARDWARE)
		{
			// Read only DAIO A2, A3, A4 and A5 pins
			int val = in8(((InputScanner*)arg)->daio_portA_handle) & 0x3C;
			//std::cout << std::hex << "val = " << val << std::endl;

			switch(val)
			{
				case 0x08: // motor overcurrent DAIO A3
					((InputScanner*)arg)->alertOvercurrent(); // set the shared variable
					break;

				case 0x04: // infrared beam interruption DAIO A2
					((InputScanner*)arg)->alertbeam(); // set the shared variable
					break;

				case 0x10: // remote button press DAIO A4
					sleep(1); // simulate a 1 second press
					((InputScanner*)arg)->alertbutton(); // set the shared variable
					break;

				case 0x20: // Simulator reset DAIO A5
					std::cout << "*** RESETTING THE SIMULATOR ***" << std::endl;
					((InputScanner*)arg)->resetSim(); // set the shared variable
					break;
			}
		}

	} while(!stopGDO);

	return 0;
}


void InputScanner::alertOvercurrent()
{
	if(::MUTEX == false)
	{
		::MUTEX = true;
		if(::OVERCURRENT != true && ::INTERRUPT != true && ::BUTTON != true)
		{
			::OVERCURRENT = true;
		}
		::MUTEX = false;
	}
}


void InputScanner::alertbeam()
{
	if(::MUTEX == false)
	{
		::MUTEX = true;
		if(::OVERCURRENT != true && ::INTERRUPT != true && ::BUTTON != true)
		{
			::INTERRUPT = true;
		}
		::MUTEX = false;
	}
}


void InputScanner::alertbutton()
{
	if(::MUTEX == false){
		::MUTEX = true;
		if(::OVERCURRENT != true && ::INTERRUPT != true && ::BUTTON != true){
			::BUTTON = true;
		}
		::MUTEX = false;
	}
}

void InputScanner::resetSim()
{
	if(::MUTEX == false)
	{
		::MUTEX = true;
		::OVERCURRENT = false;
		::INTERRUPT = false;
		::BUTTON = false;

		::RESET = true;

		::MUTEX = false;
	}
}

