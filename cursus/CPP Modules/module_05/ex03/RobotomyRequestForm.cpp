#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target)
:	AForm("Robotomy Request", 72, 45), target(target)
{
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{std::cout << "RobotomyRequestForm destructor called" << std::endl;}

void	RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	checkExecGrade(executor);
	checkIfSigned();
	if (rand() % 2)
		std::cout << "Robotomy of " << target << " has failed." << std::endl;
	else
		std::cout << "Robotomy of " << target << " is successful." << std::endl;
}
