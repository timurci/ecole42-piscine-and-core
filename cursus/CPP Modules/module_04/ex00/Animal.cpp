#include "Animal.hpp"

Animal::Animal(void)
{
	std::cout << "Animal default constructor called" << std::endl;
	type = "Animal";
}

Animal::Animal(const Animal &other)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = other;
}

Animal::~Animal(void)
{
	std::cout << "Animal destructor called" << std::endl;
}

Animal	&Animal::operator=(const Animal &other)
{
	type = other.type;
	return (*this);
}

void	Animal::makeSound(void) const
{
	std::cout << "* Indistinctive animal noise *" << std::endl;
}

std::string	Animal::getType(void) const
{
	return (type);
}
