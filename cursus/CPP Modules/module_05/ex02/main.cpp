#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main(void)
{
	Bureaucrat				b1("Cemil");
	Bureaucrat				b2("Exceptional President", 3);
	ShrubberyCreationForm	sh1("random");
	RobotomyRequestForm		rb1("Terzi");
	PresidentialPardonForm	pp1("Hasan");

	std::cout << b1 << std::endl;
	std::cout << b2 << std::endl;
	std::cout << sh1 << std::endl;
	std::cout << rb1 << std::endl;
	std::cout << pp1 << std::endl;
	b1.signForm(sh1);
	b1.executeForm(rb1);
	b2.executeForm(pp1);
	b2.signForm(sh1);
	b2.signForm(rb1);
	b2.signForm(pp1);
	b1.executeForm(rb1);
	b2.executeForm(sh1);
	b2.executeForm(rb1);
	b2.executeForm(rb1);
	b2.executeForm(rb1);
	b2.executeForm(rb1);
	b2.executeForm(pp1);

	return (0);
}
