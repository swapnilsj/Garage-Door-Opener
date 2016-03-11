#ifndef Globals_h
#define Globals_h

//Mutex is false when no thread is currently reading or setting any of the global variables
bool MUTEX = false;
bool INTERRUPT = false;
bool BUTTON = false;
bool OVERCURRENT = false;
enum STATE {CLOSED, CLOSING, OPENED, OPENING, AJAR};

#endif
