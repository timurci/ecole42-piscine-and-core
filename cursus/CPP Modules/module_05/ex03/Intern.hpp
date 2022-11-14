#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include <exception>
# include "Form.hpp"
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class	Intern
{
	
	private:
		struct s_form_entry;
		typedef struct s_form_entry t_form_entry;

	public:
		Intern(void);
		Intern(const Intern &);
		~Intern(void);

		Intern	&operator=(const Intern &);

		Form	*makeForm(std::string, std::string);
};

struct Intern::s_form_entry
{
	std::string	name;
	Form		*form_p;
};

#endif
