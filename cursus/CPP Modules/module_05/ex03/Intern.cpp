#include "Intern.hpp"

Intern::Intern(void)
{
}

Intern::Intern(const Intern &other)
{
	const void	*p = &other;

	if (p)
		return ;
}

Intern::~Intern(void)
{
}

Intern	&Intern::operator=(const Intern &other)
{
	const void	*p = &other;
	
	if (p)
		return (*this);
	return (*this);
}

Form	*Intern::makeForm(std::string form_name, std::string target_name)
{
	t_form_entry	forms[3] = 
	{
		{"shrubbery creation", new ShrubberyCreationForm(target_name)},
		{"robotomy request", new RobotomyRequestForm(target_name)},
		{"presidential pardon", new PresidentialPardonForm(target_name)}
	};

	Form	*new_form = NULL;
	for (int i = 0; i < 3; i++)
	{
		if (form_name == forms[i].name)
			new_form = forms[i].form_p;
		else
			delete forms[i].form_p;
	}

	if (new_form)
		std::cout << "Intern creates " << form_name << std::endl;
	else
		std::cout << "Intern cannot create " << form_name << std::endl;
	return (new_form);
}
