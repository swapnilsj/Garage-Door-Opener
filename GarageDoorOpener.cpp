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
    Closed stObjClosed;
    Closing stObjClosing;
    Open stObjOpen;
    Opening stObjOpening;
    StoppedClosing stObjStoppedClosing;
    StoppedOpening stObjStoppedOpening;

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
	int pid;
	int chid;
	int pulse_id = 0 ;
	timer_t timer_id;
	struct sigevent event;
	struct itimerspec timer;
	struct _pulse pulse;

	int timerCounter(10); // 10 sec timer counter

	// Create a channel to receive timer events on
	chid = ChannelCreate( 0 );
	assert ( chid != -1 );			// if returns a -1 for failure we stop with error

	// Set up the timer and timer event.
	event.sigev_notify = SIGEV_PULSE;		// most basic message we can send -- just a pulse number
	event.sigev_coid = ConnectAttach ( ND_LOCAL_NODE, 0, chid, 0, 0 );  // Get ID that allows me to communicate on the channel
	assert ( event.sigev_coid != -1 );		// stop with error if cannot attach to channel
	event.sigev_priority = getprio(0);
	event.sigev_code = 1023;				// arbitrary number assigned to this pulse
	event.sigev_value.sival_ptr = (void*)pulse_id;		// ?? TBD

	// Now create the timer and get back the timer_id value for the timer we created.
	if ( timer_create( CLOCK_REALTIME, &event, &timer_id ) == -1 )	// CLOCK_REALTIME available in all POSIX systems
	{
		perror ( "can’t create timer" );
		exit( EXIT_FAILURE );
	}

	// Change the timer configuration to set its period interval.
	// Interrupt at 1 seconds
	// Keep interrupting every 1 seconds
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_nsec = 1000000000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_nsec = 1000000000;

	// Start the timer
	if ( timer_settime( timer_id, 0, &timer, NULL ) == -1 )
	{
		perror("Can’t start timer.\n");
		exit( EXIT_FAILURE );
	}

	// Loop until 10 secs are expired
    while(timerCounter > 0) //&& No interruption occurred)
	{
		// Wait for a pulse which will arrive at each second;
    	// until then the thread will be in RECEIVE-BLOCKED state i.e. it won't take CPU cycles
		pid = MsgReceivePulse ( chid, &pulse, sizeof( pulse ), NULL );
		--timerCounter; // decrement timer counter by 1 for each 1 second
		std::cout << "Motor is running: "<< timerCounter << " seconds left to stop" << std::endl;
	}

	return 0;
}