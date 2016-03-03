#ifndef StateContext_h
#define StateContext_h

#include <vector>

#include "Set<State>.h"
#include "State.h"

class State;
class GarageDoorOpener;

class StateContext {


 private:

    virtual void transition();

    virtual void getActiveState();

 public:
    State ActiveState;
    Set<State> States;

 public:

    /**
     * @element-type State
     */
    std::vector< State* > myState;

    GarageDoorOpener *myGarageDoorOpener;
};

#endif // StateContext_h
