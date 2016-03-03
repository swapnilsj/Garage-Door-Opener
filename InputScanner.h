#ifndef InputScanner_h
#define InputScanner_h

#include "GarageDoorOpener.h"


class InputScanner {

 public:

    virtual void alertOvercurrent(void  reciever);

    virtual void alertbeam(void  reciever);

    virtual void alertbutton(void  reciever);

 public:
    Integer InputThread(scan());
    GarageDoorOpener Reciever;

 public:

    GarageDoorOpener *myGarageDoorOpener;
};

#endif // InputScanner_h
