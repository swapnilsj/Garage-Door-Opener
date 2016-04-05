#ifndef StateContext_h
#define StateContext_h

#include "State.h"
#include "GarageDoorOpener.h"
class GarageDoorOpener;

class StateContext {

 public:
	// Attributes
    GarageDoorOpener* myGarageDoorOpener;
    STATE currState;

    // Methods
    StateContext(GarageDoorOpener*, STATE);
    void transition(char);
};

#endif // StateContext_h
