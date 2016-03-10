#ifndef StateContext_h
#define StateContext_h

#include <vector>

#include "State.h"

class State;
class GarageDoorOpener;

class StateContext {

 public:

    virtual void transition(char);

    virtual State getActiveState();

    State ActiveState;
    // Set<State> States;

    // std::vector< State* > myState;

    GarageDoorOpener *myGarageDoorOpener;
};

#endif // StateContext_h
