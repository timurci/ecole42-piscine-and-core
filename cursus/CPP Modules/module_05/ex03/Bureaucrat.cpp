#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) : name("Bureaucrat")
{
	grade = 150;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : name(other.getName())
{
	grade = other.grade;
}

Bureaucrat::Bureaucrat(std::string name) : name(name)
{
	grade = 150;
}

Bureaucrat::Bureaucrat(int grade) : name("Bureaucrat")
{
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->grade = grade;
}

Bureaucrat::Bureaucrat(std::string name, int grade) : name(name)
{
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->grade = grade;
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << "Destructor called" << std::endl;
}

Bureaucrat	&Bureaucrat::operator=(const Bureaucrat &other)
{
	grade = other.grade;
	return (*this);
}

std::string	Bureaucrat::getName(void) const
{
	return (name);
}

int	Bureaucrat::getGrade(void) const
{
	return (grade);
}

void	Bureaucrat::incGrade(int size)
{
	if (grade - size < 1)
		throw Bureaucrat::GradeTooHighException();
	grade -= size;
}

void	Bureaucrat::decGrade(int size)
{
	if (grade + size > 150)
		throw Bureaucrat::GradeTooLowException();
	grade += size;
}

void	Bureaucrat::signForm(AForm &form) const
{
	if (form.getIsSigned())
	{
		std::cout << name << " couldn't sign " << form.getName()
					<< " because the form is already signed." << std::endl;
		return ;
	}
	try
	{
		form.beSigned(*this);
		std::cout << name << " signed " << form.getName() << std::endl;
	}
	catch (std::exception &exc)
	{
		std::cout << name << " couldn't sign " << form.getName()
					<< " because " << exc.what() << "." << std::endl;
	}
}

void	Bureaucrat::executeForm(AForm &form) const
{
	try
	{
		form.execute(*this);
		std::cout << name << " executed " << form.getName() << std::endl;
	}
	catch(std::exception &exc)
	{
		std::cout << name << " couldn't execute " << form.getName()
					<< " because " << exc.what() << "." << std::endl;
	}
}

const char	*Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Grade Too High");
}

const char	*Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Grade Too Low");
}

std::ostream	&operator<<(std::ostream &ost, const Bureaucrat &obj)
{
	ost << obj.getName() << ", bureaucrat grade " << obj.getGrade();
	return (ost);
}
