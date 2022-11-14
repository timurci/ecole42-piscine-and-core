#include "Form.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int	main(void)
{
	Bureaucrat				b1("Cemil");
	Bureaucrat				b2("Exceptional President", 3);
	Intern					i1;
	Form					*forms[4] = {};

	forms[0] = i1.makeForm("shrubbery creation", "random");
	forms[1] = i1.makeForm("robotomy request", "Terzi");
	forms[2] = i1.makeForm("presidential pardon", "Hasan");
	forms[3] = i1.makeForm("hello world!", "program");

	std::cout << b1 << std::endl;
	std::cout << b2 << std::endl;
	std::cout << *forms[0] << std::endl;
	std::cout << *forms[1] << std::endl;
	std::cout << *forms[2] << std::endl;
	b1.signForm(*forms[0]);
	b1.executeForm(*forms[1]);
	b2.executeForm(*forms[2]);
	b2.signForm(*forms[0]);
	b2.signForm(*forms[1]);
	b2.signForm(*forms[2]);
	b1.executeForm(*forms[0]);
	b2.executeForm(*forms[0]);
	b2.executeForm(*forms[1]);
	b2.executeForm(*forms[1]);
	b2.executeForm(*forms[1]);
	b2.executeForm(*forms[1]);
	b2.executeForm(*forms[2]);

	return (0);
}
