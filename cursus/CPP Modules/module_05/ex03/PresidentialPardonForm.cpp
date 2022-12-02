#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target)
:	AForm("Presidential Pardon", 25, 5), target(target)
{
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{std::cout << "PresidentialPardonForm destructor called" << std::endl;}

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	checkExecGrade(executor);
	checkIfSigned();
	std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
