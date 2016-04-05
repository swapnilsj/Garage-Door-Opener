#include "StateContext.h"


StateContext::StateContext(GarageDoorOpener* gdo, STATE currSt){
	myGarageDoorOpener = gdo;
	currState = currSt;
}


void StateContext::transition(char event)
{
	//Overcurrent
	if(event == 'O')
	{
		if(currState == CLOSED)
		{
			currState = CLOSED;
		}

		else if(currState == CLOSING)
		{
			myGarageDoorOpener->ClosingState.Exit();
			myGarageDoorOpener->OpeningState.Entry();
			currState = OPENING;
		}

		else if(currState == OPEN)
		{
			currState = OPEN;
		}

		else if(currState == OPENING)
		{
			if(::SIMULATION == HARDWARE)
			{
				out8(myGarageDoorOpener->daio_portB_handle, 0x10);//stop counter
				myGarageDoorOpener->hwFlag = false;
			}
			myGarageDoorOpener->OpeningState.Exit();
			myGarageDoorOpener->SOState.Entry();
			currState = STOPPEDOPENING;
		}

		else if(currState == STOPPEDCLOSING)
		{
			currState = STOPPEDCLOSING;
		}

		else if(currState == STOPPEDOPENING)
		{
			currState = STOPPEDOPENING;
		}

	}

	//Beam Interrupt
	if(event == 'I')
	{
		if(currState == CLOSED)
		{
			currState = CLOSED;
		}

		else if(currState == CLOSING)
		{
			if(::SIMULATION == HARDWARE)
			{
				//out8(myGarageDoorOpener->daio_portB_handle, 0x10);//stop counter
				myGarageDoorOpener->hwFlag = false;
			}
			myGarageDoorOpener->ClosingState.Exit();
			myGarageDoorOpener->OpeningState.Entry();
			currState = OPENING;
		}

		else if(currState == OPEN)
		{
			currState = OPEN;
		}

		else if(currState == OPENING)
		{
			currState = OPENING;
		}

		else if(currState == STOPPEDCLOSING)
		{
			currState = STOPPEDCLOSING;
		}

		else if(currState == STOPPEDOPENING)
		{
			currState = STOPPEDOPENING;
		}
	}

	//Button Press
	if(event == 'P')
	{
		if(currState == CLOSED)
		{
			myGarageDoorOpener->ClosedState.Exit();
			myGarageDoorOpener->OpeningState.Entry();
			currState = OPENING;
		}

		else if(currState == CLOSING)
		{
			if(::SIMULATION == HARDWARE)
			{
				out8(myGarageDoorOpener->daio_portB_handle, 0x10);//stop counter
				myGarageDoorOpener->hwFlag = false;
			}
			myGarageDoorOpener->ClosingState.Exit();
			myGarageDoorOpener->SCState.Entry();
			currState = STOPPEDCLOSING;
		}

		else if(currState == OPEN)
		{
			myGarageDoorOpener->OpenState.Exit();
			myGarageDoorOpener->ClosingState.Entry();
			currState = CLOSING;
		}

		else if(currState == OPENING)
		{
			if(::SIMULATION == HARDWARE)
			{
				out8(myGarageDoorOpener->daio_portB_handle, 0x10);//stop counter
				myGarageDoorOpener->hwFlag = false;
			}
			myGarageDoorOpener->OpeningState.Exit();
			myGarageDoorOpener->SOState.Entry();
			currState = STOPPEDOPENING;
		}

		else if(currState == STOPPEDCLOSING)
		{
			myGarageDoorOpener->SCState.Exit();
			myGarageDoorOpener->OpeningState.Entry();
			currState = OPENING;
		}

		else if(currState == STOPPEDOPENING)
		{
			myGarageDoorOpener->SOState.Exit();
			myGarageDoorOpener->ClosingState.Entry();
			currState = CLOSING;
		}
	}

	//Door closed or Door opened completely
	if(event == 'F')
	{
		if(currState == CLOSED)
		{
			currState = CLOSED;
		}

		else if(currState == CLOSING)
		{
			myGarageDoorOpener->ClosingState.Exit();
			myGarageDoorOpener->ClosedState.Entry();
			currState = CLOSED;
		}

		else if(currState == OPEN)
		{
			currState = OPEN;
		}

		else if(currState == OPENING)
		{
			myGarageDoorOpener->OpeningState.Exit();
			myGarageDoorOpener->OpenState.Entry();
			currState = OPEN;
		}

		else if(currState == STOPPEDCLOSING)
		{
			currState = STOPPEDCLOSING;
		}

		else if(currState == STOPPEDOPENING)
		{
			currState = STOPPEDOPENING;
		}

	}

	//RESET SIMULATOR
	if(event == 'R')
	{
		if(currState == CLOSED)
		{
			currState = CLOSED;
		}

		else if(currState == CLOSING)
		{
			myGarageDoorOpener->ClosingState.Exit();
			myGarageDoorOpener->ClosedState.Entry();
			currState = CLOSED;
		}

		else if(currState == OPEN)
		{
			myGarageDoorOpener->OpenState.Exit();
			myGarageDoorOpener->ClosedState.Entry();
			currState = CLOSED;
		}

		else if(currState == OPENING)
		{
			myGarageDoorOpener->OpeningState.Exit();
			myGarageDoorOpener->ClosedState.Entry();
			currState = CLOSED;
		}

		else if(currState == STOPPEDCLOSING)
		{
			myGarageDoorOpener->SCState.Exit();
			myGarageDoorOpener->ClosedState.Entry();
			currState = CLOSED;
		}

		else if(currState == STOPPEDOPENING)
		{
			myGarageDoorOpener->SOState.Exit();
			myGarageDoorOpener->ClosedState.Entry();
			currState = CLOSED;
		}
	}
}

