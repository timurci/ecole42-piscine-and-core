#include "Bureaucrat.hpp"

int	main(void)
{
	Bureaucrat	b1("Cemil");

	std::cout << b1 << std::endl;
	b1.incGrade(100);
	std::cout << b1 << std::endl;
	b1.incGrade(100);
	std::cout << b1 << std::endl;
	b1.decGrade(150);
	std::cout << b1 << std::endl;
	b1.decGrade(150);
	std::cout << b1 << std::endl;
	return (0);
}
