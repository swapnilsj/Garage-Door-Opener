#ifndef GarageDoorOpener_h
#define GarageDoorOpener_h

#include "InputScanner.h"
#include "StateContext.h"
#include "Thread.h"


class GarageDoorOpener {


 private:

    virtual void Main();

 public:
    Thread GDOThread;

 public:

    InputScanner myInputScanner;

    StateContext myStateContext;
};

#endif // GarageDoorOpener_h
