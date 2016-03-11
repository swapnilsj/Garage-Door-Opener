#include "StateContext.h"


void StateContext::transition(char event)
{
	//Overcurrent
	if(event == 'O'){
		if(this->ActiveState.tOvercurrent() != 0){
			this->ActiveState.Exit();
			this->ActiveState = ActiveState.tOvercurrent();
			this->ActiveState.Entry();

		}
	}
	//Beam Interrupt
	if(event == 'I'){
		if(this->ActiveState.tBeam() != 0){
			this->ActiveState.Exit();
			this->ActiveState = ActiveState.tBeam();
			this->ActiveState.Entry();
		}
	}
	//Button Press
	if(event == 'P'){
		if(this->ActiveState.tButton() != 0){
			this->ActiveState.Exit();
			this->ActiveState = ActiveState.tButton();
			this->ActiveState.Entry();
		}
	}
	//Door closed
	if(event == 'C'){
		if(this->ActiveState.tClosed() != 0){
			this->ActiveState.Exit();
			this->ActiveState = ActiveState.tClosed();
			this->ActiveState.Entry();
		}
	}
	//Door Ajar
	if(event == 'A'){
		if(this->ActiveState.tOpened() != 0){
			this->ActiveState.Exit();
			this->ActiveState = ActiveState.tOpened();
			this->ActiveState.Entry();
		}
	}
}

State StateContext::getActiveState()
{
	return(this->ActiveState);
}
