#include "State.h"


void State::Entry()
{
	std::cout << "State:Entry" << std::endl;
}

void State::Exit()
{
	std::cout << "State:Exit" << std::endl;
}

void Closed::Entry()
{
	std::cout << "Garage Door Closed. Beam off\n";
	::SETMOTORDOWN = false;
	::SETMOTORUP = false;
	::SETBEAM = false;
}

void Closed::Exit()
{
	std::cout << "Beam off" << std::endl;
}

void Closing::Entry()
{
	std::cout << "Garage Door Closing, beam on" << std::endl;
	::SETMOTORDOWN = true;
	::SETMOTORUP = false;
	::SETBEAM = true;
}

void Closing::Exit()
{
	std::cout << "Beam off" << std::endl;
}

void Open::Entry()
{
	std::cout << "Garage door opened, beam off" << std::endl;
	::SETMOTORDOWN = false;
	::SETMOTORUP = false;
	::SETBEAM = false;
}

void Open::Exit()
{

}

void Opening::Entry()
{
	std::cout << "Garage Door Opening, beam off\n" << std::endl;
	::SETMOTORDOWN = false;
	::SETMOTORUP = true;
	::SETBEAM = false;
}

void Opening::Exit()
{

}

void StoppedClosing::Entry()
{
	std::cout << "Garage Door Stopped Closing\n" << std::endl;
	::SETMOTORDOWN = false;
	::SETMOTORUP = false;
	::SETBEAM = false;
}

void StoppedClosing::Exit()
{

}

void StoppedOpening::Entry()
{
	std::cout << "Garage Door Stopped Opening, beam off\n" << std::endl;
	::SETMOTORDOWN = false;
	::SETMOTORUP = false;
	::SETBEAM = false;
}

void StoppedOpening::Exit()
{

}

