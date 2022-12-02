#include "AForm.hpp"

AForm::AForm(void) : name("AForm"), sign_grade(150), exec_grade(150), is_signed(0)
{
}

AForm::AForm(const AForm &other) : name(other.name), sign_grade(other.sign_grade),
								exec_grade(other.exec_grade),
								is_signed(other.is_signed)
{
}

AForm::AForm(std::string name, int sign_grade, int exec_grade) : name(name),
								sign_grade(sign_grade), exec_grade(exec_grade),
								is_signed(0)
{
	if (sign_grade < 1 || exec_grade < 1)
		throw AForm::GradeTooHighException();
	else if (sign_grade > 150 || exec_grade > 150)
		throw AForm::GradeTooLowException();
}

AForm::~AForm(void)
{
	std::cout << "AForm destructor called" << std::endl;
}

AForm	&AForm::operator=(const AForm &other)
{
	is_signed = other.is_signed;
	return (*this);
}

std::string	AForm::getName(void) const
{return (name);}

int	AForm::getSignGrade(void) const
{return (sign_grade);}

int	AForm::getExecGrade(void) const
{return (exec_grade);}

bool	AForm::getIsSigned(void) const
{return (is_signed);}

void	AForm::beSigned(const Bureaucrat &br)
{
	if (br.getGrade() > sign_grade)
		throw AForm::GradeTooLowException();
	is_signed = 1;
}

void	AForm::checkExecGrade(const Bureaucrat &br) const
{
	if (br.getGrade() > exec_grade)
		throw AForm::GradeTooLowException();
}

void	AForm::checkIfSigned(void) const
{
	if (!is_signed)
		throw AForm::SignException();
}

const char	*AForm::GradeTooHighException::what(void) const throw()
{return ("Grade is too high");}

const char	*AForm::GradeTooLowException::what(void) const throw()
{return ("Grade is too low");}

const char	*AForm::SignException::what(void) const throw()
{return ("Form is not signed");}

std::ostream	&operator<<(std::ostream &ost, const AForm &form)
{
	ost << "Form " << form.getName()
					<< (form.getIsSigned() ? " is signed " : " is not signed ")
					<< "and requires grade " << form.getSignGrade()
					<< " to be signed.";
	return (ost);
}
