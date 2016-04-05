#ifndef InputScanner_h
#define InputScanner_h

#include "Globals.h"
#include <pthread.h>
#include <iostream.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include <unistd.h>       // for sleep()
#include <stdint.h>       // for uintptr_t
#include <hw/inout.h>     // for in*() and out*() functions
#include <sys/mman.h>     // for mmap_device_io()
#include <inttypes.h>     // for ClockCycles() return value

class InputScanner
{

 public:
	pthread_t inputScannerThreadID;

	InputScanner();
	~InputScanner();
	static void* InputScannerThread(void* arg);
    void alertOvercurrent();
    void alertbeam();
    void alertbutton();
    void resetSim();

    // HARDWARE SIMULATION
	// Handle variables for memory mapped registers
	uintptr_t daio_ctrl_handle;
	uintptr_t daio_portA_handle;

};

#endif // InputScanner_h
