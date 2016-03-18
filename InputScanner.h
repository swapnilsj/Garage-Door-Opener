#ifndef InputScanner_h
#define InputScanner_h

#include "Globals.h"
#include <pthread.h>
#include <iostream.h>
#include <unistd.h>

class InputScanner
{

 public:

	InputScanner();
	~InputScanner();
	pthread_t inputScannerThreadID;
    static void* InputScannerThread(void* arg);
    void alertOvercurrent();
    void alertbeam();
    void alertbutton();
};

#endif // InputScanner_h
