#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

# include <string>
# include <iostream>
# include <exception>
# include "Form.hpp"

class	Form;

class	Bureaucrat
{
	private:
		const std::string	name;
		int					grade;

	public:
		Bureaucrat(void);
		Bureaucrat(const Bureaucrat &);
		Bureaucrat(std::string n);
		Bureaucrat(int);
		Bureaucrat(std::string n, int);
		~Bureaucrat(void);

		Bureaucrat	&operator=(const Bureaucrat &);

		std::string	getName(void) const;
		int			getGrade(void) const;
		
		void		incGrade(int);
		void		decGrade(int);
		void		signForm(Form &) const;
		void		executeForm(Form &) const;

		//Exceptions
		class		GradeTooHighException : public std::exception
		{public: virtual const char	*what(void) const throw();};
		class		GradeTooLowException : public std::exception
		{public: virtual const char	*what(void) const throw();};
};

std::ostream	&operator<<(std::ostream &, const Bureaucrat &);

#endif
