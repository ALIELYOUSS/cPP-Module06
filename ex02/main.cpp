#include "Base.hpp"

#include <ctime>
#include <cstdlib>
#include <iostream>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	Base* object = generate();
	std::cout << "pointer: ";
	identify(object);
	std::cout << std::endl;
	std::cout << "reference: ";
	identify(*object);
	std::cout << std::endl;
	delete object;
	return 0;
}
