#include "GarageDoorOpener.h"

// GarageDoorOpener constructor
GarageDoorOpener::GarageDoorOpener()
{
	receivedInput = 'x'; // Initialized to default
	InputScanner myInputScanner;
	motorDown = false;
	motorUp = false;
	beamOn = false;
	
	//create state objects here
	
	

	// create the inputscanner thread
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);		// initialize thread attributes structure
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&GDOThread, &threadAttr, &InputScanner::InputScannerThread, &myInputScanner);

}

// GarageDoorOpener destructor
GarageDoorOpener::~GarageDoorOpener()
{
	// What should go here?
}

void setmotorDown(bool arg){
	
}

void setmotorUp(bool arg){
	
}

void setBeam(bool arg){
	
}

void* DoorThread(void* param){
	
}