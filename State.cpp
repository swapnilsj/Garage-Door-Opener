#include "State.h"


void State::Entry()
{

}


void State::Exit()
{

}

State State::tOvercurrent()
{
	return(this->Overcurrent);
}

State State::tBeam()
{
	return(this->Beam);
}

State State::tButton()
{
	return(this->Button);
}

State State::tClosed()
{
	return(this->Closed);
}

State State::tOpened()
{
	return(this->Opened);
}

void State::setTransitions(State OC, State I, State B, State OP, State C)
{
	this->Overcurrent = OC;
	this->Beam = I;
	this->Button = B;
	this->Closed = C;
	this->Opened = OP;
}

