#include "Form.hpp"

Form::Form(void) : name("Form"), sign_grade(150), exec_grade(150), is_signed(0)
{
}

Form::Form(const Form &other) : name(other.name), sign_grade(other.sign_grade),
								exec_grade(other.exec_grade),
								is_signed(other.is_signed)
{
}

Form::Form(std::string name, int sign_grade, int exec_grade) : name(name),
								sign_grade(sign_grade), exec_grade(exec_grade),
								is_signed(0)
{
	if (sign_grade < 1 || exec_grade < 1)
		throw Form::GradeTooHighException();
	else if (sign_grade > 150 || exec_grade > 150)
		throw Form::GradeTooLowException();
}

Form::~Form(void)
{
	std::cout << "Form destructor called" << std::endl;
}

Form	&Form::operator=(const Form &other)
{
	is_signed = other.is_signed;
	return (*this);
}

std::string	Form::getName(void) const
{return (name);}

int	Form::getSignGrade(void) const
{return (sign_grade);}

int	Form::getExecGrade(void) const
{return (exec_grade);}

bool	Form::getIsSigned(void) const
{return (is_signed);}

void	Form::beSigned(const Bureaucrat &br)
{
	if (br.getGrade() > sign_grade)
		throw Form::GradeTooLowException();
	is_signed = 1;
}

void	Form::checkExecGrade(const Bureaucrat &br) const
{
	if (br.getGrade() > exec_grade)
		throw Form::GradeTooLowException();
}

void	Form::checkIfSigned(void) const
{
	if (!is_signed)
		throw Form::SignException();
}

const char	*Form::GradeTooHighException::what(void) const throw()
{return ("Grade is too high");}

const char	*Form::GradeTooLowException::what(void) const throw()
{return ("Grade is too low");}

const char	*Form::SignException::what(void) const throw()
{return ("Form is not signed");}

std::ostream	&operator<<(std::ostream &ost, const Form &form)
{
	ost << "Form " << form.getName()
					<< (form.getIsSigned() ? " is signed " : " is not signed ")
					<< "and requires grade " << form.getSignGrade()
					<< " to be signed.";
	return (ost);
}
