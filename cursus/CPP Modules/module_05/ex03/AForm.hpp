#ifndef AFORM_HPP
# define AFORM_HPP

# include <string>
# include <iostream>
# include <exception>
# include "Bureaucrat.hpp"

class	Bureaucrat;

class	AForm
{
	private:
		const std::string	name;
		const int			sign_grade;
		const int			exec_grade;
		bool				is_signed;

	public:
		AForm(void);
		AForm(const AForm &);
		AForm(std::string, int, int);
		virtual ~AForm(void);

		AForm			&operator=(const AForm &);

		std::string		getName(void) const;
		int				getSignGrade(void) const;
		int				getExecGrade(void) const;
		bool			getIsSigned(void) const;

		void			beSigned(const Bureaucrat &);
		void			checkExecGrade(const Bureaucrat &) const;
		void			checkIfSigned(void) const;
		
		virtual void	execute(Bureaucrat const &executor) const = 0;

		//Exceptions
		class			GradeTooHighException : public std::exception
		{public: virtual const char	*what(void) const throw();};
		class			GradeTooLowException : public std::exception
		{public: virtual const char	*what(void) const throw();};
		class			SignException : public std::exception
		{public: virtual const char	*what(void) const throw();};
};

std::ostream	&operator<<(std::ostream &, const AForm &);

#endif
