#include "Opening.h"

void State::Entry(){
	std::cout << "Garage Door Opening, beam on\n" << std::endl;
}

void State::Exit(){
	std::cout << "Beam off\n" << std::endl;
}
