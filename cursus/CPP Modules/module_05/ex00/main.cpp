#include "Bureaucrat.hpp"
#include <iostream>
#include <exception>

void	inc(Bureaucrat &b, int n)
{
	try
	{b.incGrade(n);}
	catch (std::exception &exc)
	{std::cout << "Error: " << exc.what() << std::endl;}
}

void	dec(Bureaucrat &b, int n)
{
	try
	{b.decGrade(n);}
	catch (std::exception &exc)
	{std::cout << "Error: " << exc.what() << std::endl;}
}

int	main(void)
{
	Bureaucrat	b1("Cemil");

	std::cout << b1 << std::endl;
	inc(b1, 100);
	std::cout << b1 << std::endl;
	inc(b1, 100);
	std::cout << b1 << std::endl;
	dec(b1, 50);
	std::cout << b1 << std::endl;
	dec(b1, 150);
	std::cout << b1 << std::endl;
	return (0);
}
