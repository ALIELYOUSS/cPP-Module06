#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base::~Base() {}

Base* generate(void)
{
	switch (std::rand() % 3) {
		case 0: return new A();
		case 1: return new B();
		default: return new C();
	}
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A";
	else if (dynamic_cast<B*>(p))
		std::cout << "B";
	else if (dynamic_cast<C*>(p))
		std::cout << "C";
}

void identify(Base& p)
{
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A";
	}
	catch(...) {
		try {
			(void)dynamic_cast<B&>(p);
			std::cout << "B";
		} 
		catch (...) {
			(void)dynamic_cast<C&>(p);
			std::cout << "C";
		}
	}
}