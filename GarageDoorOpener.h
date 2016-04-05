#ifndef GarageDoorOpener_h
#define GarageDoorOpener_h

#include <iostream>
#include <ctype.h>
#include <string>
#include <iomanip>

// QNX Libraries
#include <pthread.h>      // pthread function calls
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>  // SYSPAGE_ENTRY() function
#include <time.h>
#include <unistd.h>       // for sleep()
#include <stdint.h>       // for uintptr_t
#include <hw/inout.h>     // for in*() and out*() functions
#include <sys/mman.h>     // for mmap_device_io()
#include <inttypes.h>     // for ClockCycles() return value

#include "State.h"
#include "Globals.h"
#include "StateContext.h"

class InputScanner;
class StateContext;

class GarageDoorOpener {

 public:
 	
	pthread_t GDOThreadID;
    StateContext* myStateContext;

    GarageDoorOpener();		// constructor
    ~GarageDoorOpener();	// destructor
    static void* DoorThread(void*);
    
	Closed ClosedState;
	Closing ClosingState;
	Open OpenState;
	Opening OpeningState;
	StoppedClosing SCState;
	StoppedOpening SOState;

	int count;

	// HARDWARE SIMULATION
	// Handle variables for memory mapped registers
	uintptr_t daio_ctrl_handle;
	uintptr_t daio_portB_handle;
	uintptr_t daio_portC_handle;
	bool hwFlag;

	int setHWConns(void);
	bool resetHWSimulator(void);
};

#endif // GarageDoorOpener_h
