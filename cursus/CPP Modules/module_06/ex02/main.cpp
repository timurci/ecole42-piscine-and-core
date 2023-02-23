#include <iostream>
#include <cstdlib>
#include <exception>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#ifndef ARRAY_SIZE
# define ARRAY_SIZE 3
#endif

Base	*generate(void)
{
	switch(rand() % 3)
	{
		case 0:
			return (new A);
		case 1:
			return (new B);
		case 2:
			return (new C);
		default:
			return (NULL);
	}
}

void	identify(Base *p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A";
	else if (dynamic_cast<B*>(p))
		std::cout << "B";
	else if (dynamic_cast<C*>(p))
		std::cout << "C";
}

void	identify(Base &p)
{
	try
	{
		A	x = dynamic_cast<A&>(p);
		std::cout << "A";
	} catch(std::exception &exc){}
	try
	{
		B	y = dynamic_cast<B&>(p);
		std::cout << "B";
	}catch(std::exception &exc){}
	try
	{
		C	z = dynamic_cast<C&>(p);
		std::cout << "C";
	}catch(std::exception &exc){}
}

int	main(void)
{
	Base	*p[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++)
		p[i] = generate();
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		std::cout << "P: ";
		identify(p[i]);
		std::cout << "\tR: ";
		identify(*p[i]);
		std::cout << std::endl;
	}
	for (int i = 0; i < ARRAY_SIZE; i++)
		delete p[i];
	return (0);
}
