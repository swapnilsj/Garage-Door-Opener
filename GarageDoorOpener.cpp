#include "GarageDoorOpener.h"


// GarageDoorOpener constructor
GarageDoorOpener::GarageDoorOpener()
{
	receivedInput = 'x'; // Initialized to default
	event = 'x';

	motorDown = false;
	motorUp = false;
	beamOn = false;

	InputScanner myInputScanner;
    StateContext myStateContext;

    // create state objects here


    //

	// create the inputscanner thread
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);		// initialize thread attributes structure
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&inputScannerThreadID, &threadAttr, &InputScanner::InputScannerThread, &myInputScanner);

}

// GarageDoorOpener destructor
GarageDoorOpener::~GarageDoorOpener()
{
	// input scanner will join when GDO object is no longer available
	pthread_join(inputScannerThreadID, NULL);

	// What else should go here?
}

void setmotorDown(bool arg)
{

}

void setmotorUp(bool arg)
{

}

void setBeam(bool arg)
{

}

void* DoorThread(void* param)
{
	return 0;
}