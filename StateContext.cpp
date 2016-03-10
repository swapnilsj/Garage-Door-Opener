#include "StateContext.h"


void StateContext::transition(char event)
{
	//Overcurrent
	if(event == 'O'){
		if(ActiveState.tOvercurrent() != 0){
			ActiveState.Exit();
			*ActiveState = ActiveState.tOvercurrent();
			*ActiveState.Entry();

		}
	}
	//Beam Interrupt
	if(event == 'I'){
		if(this.ActiveState.tBeam() != 0){
			this.ActiveState.exit();
			this.ActiveState = ActiveState.tBeam();
			this.ActiveState.entry();
		}
	}
	//Button Press
	if(event == 'P'){
		if(this.ActiveState.tButton() != 0){
			this.ActiveState.exit();
			this.ActiveState = ActiveState.tButton();
			this.ActiveState.entry();
		}
	}
	//Door closed
	if(event == 'C'){
		if(this.ActiveState.tClosed() != 0){
			this.ActiveState.exit();
			this.ActiveState = ActiveState.tClosed();
			this.ActiveState.entry();
		}
	}
	//Door Ajar
	if(event == 'A'){
		if(this.ActiveState.tOpened() != 0){
			this.ActiveState.exit();
			this.ActiveState = ActiveState.tOpened();
			this.ActiveState.entry();
		}
	}
}

State StateContext::getActiveState()
{
	return(this->ActiveState);
}
