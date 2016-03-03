#ifndef State_h
#define State_h

class StateContext;

class State {

 public:

    virtual void Entry();

    virtual void Exit();

 public:

    StateContext *myStateContext;
};

#endif // State_h
