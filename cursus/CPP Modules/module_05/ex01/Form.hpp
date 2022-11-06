#ifndef FORM_HPP
# define FORM_HPP

# include <string>
# include <iostream>
# include <exception>
# include "Bureaucrat.hpp"

class	Bureaucrat;

class	Form
{
	private:
		const std::string	name;
		const int			sign_grade;
		const int			exec_grade;
		bool				is_signed;

	public:
		Form(void);
		Form(const Form &);
		Form(std::string, int, int);
		~Form(void);

		Form	&operator=(const Form &);

		std::string	getName(void) const;
		int			getSignGrade(void) const;
		int			getExecGrade(void) const;
		bool		getIsSigned(void) const;

		void		beSigned(const Bureaucrat &);

		//Exceptions
		class		GradeTooHighException : public std::exception
		{public: virtual const char	*what(void) const throw();};
		class		GradeTooLowException : public std::exception
		{public: virtual const char	*what(void) const throw();};
};

std::ostream	&operator<<(std::ostream &, const Form &);

#endif
