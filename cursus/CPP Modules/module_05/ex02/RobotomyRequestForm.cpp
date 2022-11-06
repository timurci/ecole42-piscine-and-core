#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target)
:	Form("Robotomy Request", 72, 45), target(target), drilled(0)
{
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{std::cout << "RobotomyRequestForm destructor called" << std::endl;}

void	RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	checkExecGrade(executor);
	checkIfSigned();
	if (drilled)
	{
		std::cout << "Robotomy of " << target << " has failed." << std::endl;
		drilled = 0;
	}
	else
	{
		std::cout << "Robotomy of " << target << " is successful." << std::endl;
		drilled = 1;
	}
}
