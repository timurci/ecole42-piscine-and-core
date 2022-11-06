#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

#define ARRAY_SIZE 2

int	main(void)
{
	const Animal	*animals[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (i < ARRAY_SIZE / 2)
			animals[i] = new Dog;
		else
			animals[i] = new Cat;
	}

	for (int i = 0; i < ARRAY_SIZE; i++)
		delete animals[i];
	return (0);
}
