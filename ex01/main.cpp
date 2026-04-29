#include "Serializer.hpp"

#include <iostream>

int main()
{
	Data data;
	data.id = 42;
	data.name = "Module 06";
	data.score = 1337.0;

	Data* original = &data;
	uintptr_t raw = Serializer::serialize(original);
	Data* restored = Serializer::deserialize(raw);

	std::cout << "original: " << original << std::endl;
	std::cout << "raw: " << raw << std::endl;
	std::cout << "restored: " << restored << std::endl;
	std::cout << "same pointer: " << std::boolalpha << (original == restored) << std::endl;
	return 0;
}