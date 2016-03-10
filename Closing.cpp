#include "Closing.h"

void State::Entry(){
	std::cout << "Garage Door Closing, beam on" << std::endl;
}

void State::Exit(){
	std::cout << "Beam off" << std::endl;
}



