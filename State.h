#ifndef State_h
#define State_h
#include <iostream>;
class StateContext;

class State {

 public:

	/*
	 * Entry actions on a state change
	 */
    virtual void Entry();

    /*
     * Exit actions on a state change
     */
    virtual void Exit();

    /*
     * The following five functions represent transitions
     * Each state will know what state it should transistion in an event
     * If it does not tranistion during an event it returns NULL
     */
    virtual State tOvercurrent();
    virtual State tBeam();
    virtual State tButton();
    virtual State tClosed();
    virtual State tOpened();

    void setTransitions(State, State, State, State, State);


 protected:

    GarageDoorOpener *reciever;
    StateContext *myStateContext;
    State *Overcurrent;
    State *Beam;
    State *Button;
    State *Closed;
    State *Opened;
};

#endif // State_h
