#include "GarageDoorOpener.h"

bool TRANSITIONED = false;
bool SETMOTORDOWN = false;
bool SETMOTORUP = false;
bool SETBEAM = false;
bool MUTEX = false;
bool INTERRUPT = false;
bool BUTTON = false;
bool OVERCURRENT = false;

// GarageDoorOpener constructor
GarageDoorOpener::GarageDoorOpener()
{
	count = 0;

	// create state objects here
	Closed ClosedState;
	Closing ClosingState;
	Open OpenState;
	Opening OpeningState;
	StoppedClosing SCState;
	StoppedOpening SOState;
	
	//Overcurrent, interrupt, button, finished
	ClosedState.setTransitions(0, 0 , &OpeningState, 0);
	ClosingState.setTransitions(&OpeningState, &OpeningState, &SCState, &ClosedState);
	OpenState.setTransitions(0, 0, &ClosingState, 0);
	OpeningState.setTransitions(&SOState, 0, &SOState, &OpenState);
	SCState.setTransitions(0, 0, &OpeningState, 0);
	SOState.setTransitions(0, 0, &ClosingState, 0);

    myStateContext = new StateContext(&ClosedState);

    // create the inputscanner thread
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);		// initialize thread attributes structure
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&GDOThreadID, &threadAttr, &GarageDoorOpener::DoorThread, this);

}

// GarageDoorOpener destructor
GarageDoorOpener::~GarageDoorOpener()
{
	// input scanner will join when GDO object is no longer available
    pthread_join(GDOThreadID, NULL);

	// What else should go here?
}


// Thread to be called when Door is opening or closing
void* GarageDoorOpener::DoorThread(void* param)
{
	while(1)
	{
		//Printing the countdown if the door is moving
		if(::SETMOTORDOWN == true || ::SETMOTORUP == true)
		{
			std::cout << ((GarageDoorOpener*)param)->count << std::endl;
		}
		//Garage door has fully closed or opened
		if(((GarageDoorOpener*)param)->count == 10 && (::SETMOTORUP == true || ::SETMOTORDOWN == true))
		{
			((GarageDoorOpener*)param)->myStateContext->transition('F');
			((GarageDoorOpener*)param)->count = 0;
			continue;
		}
		//Looking for messages from inputscanner
		if(::MUTEX == false)
		{
			::MUTEX = true;
			if(::OVERCURRENT == true)
			{
				((GarageDoorOpener*)param)->myStateContext->transition('O');
			}
			if(::BUTTON == true)
			{
				((GarageDoorOpener*)param)->myStateContext->transition('P');
			}
			if(::INTERRUPT == true && ::SETBEAM == true)
			{
				((GarageDoorOpener*)param)->myStateContext->transition('I');
			}

			::MUTEX = false;

			if(::TRANSITIONED)
			{
				((GarageDoorOpener*)param)->count = 0;
				::TRANSITIONED = false;
				continue;
			}
		}

		((GarageDoorOpener*)param)->count++;
		sleep(1);
	}
	return 0;
}
