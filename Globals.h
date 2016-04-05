#ifndef Globals_h
#define Globals_h

	// Mutex is false when no thread is currently reading 
	// or setting any of the global variables
	extern bool MUTEX;
	extern bool INTERRUPT;
	extern bool BUTTON;
	extern bool OVERCURRENT;
	// TRANSITIONED lets garagedooropener know 
	// if a state transition happened
	extern bool TRANSITIONED;
	extern bool SETMOTORDOWN;
	extern bool SETMOTORUP;
	extern bool SETBEAM;
	extern bool RESET;
	extern bool stopGDO;
	extern bool SIMULATION;



    enum STATE {CLOSED, CLOSING, OPEN, OPENING, STOPPEDCLOSING, STOPPEDOPENING};
    enum SIMOPTION {HARDWARE, SOFTWARE};

    // HARDWARE SIMULATION
	// Port length and memory mapped register addresses
	#define PORT_LENGTH                 1
	#define BASE_ADDRESS                0x280
	#define DAIO_PORTA_ADDRESS          0x08  // For voltage data
	#define DAIO_PORTB_ADDRESS          0x09  // For SyncClock
	#define DAIO_PORTC_ADDRESS          0x0A  // For parity bit
	#define DAIO_CONTROLREG_ADDRESS     0x0B

#endif

