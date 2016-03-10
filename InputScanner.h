#ifndef InputScanner_h
#define InputScanner_h

#include "GarageDoorOpener.h"


class InputScanner
{

 public:

    static void* InputScannerThread(void* arg);
    virtual void alertOvercurrent();
    virtual void alertbeam();
    virtual void alertbutton();


    //GarageDoorOpener *myGarageDoorOpener;
};

#endif // InputScanner_h
