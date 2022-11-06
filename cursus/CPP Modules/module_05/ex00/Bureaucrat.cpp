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

const std::string	Bureaucrat::getName(void) const
{
	return (name);
}

int	Bureaucrat::getGrade(void) const
{
	return (grade);
}

void	Bureaucrat::incGrade(int size)
{
	try
	{
		if (grade - size < 1)
			throw Bureaucrat::GradeTooHighException();
		grade -= size;
	}
	catch (std::exception &exc)
	{std::cout << exc.what() << std::endl;}
}

void	Bureaucrat::decGrade(int size)
{
	try
	{
		if (grade + size > 150)
			throw Bureaucrat::GradeTooLowException();
		grade += size;
	}
	catch (std::exception &exc)
	{std::cout << exc.what() << std::endl;}
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
