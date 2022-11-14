#ifndef PRESIDENTIAL_PARDON_FORM
# define PRESIDENTIAL_PARDON_FORM

# include "Form.hpp"
# include "Bureaucrat.hpp"

class PresidentialPardonForm : public Form
{
	private:
		std::string	target;

	public:
		PresidentialPardonForm(std::string);
		~PresidentialPardonForm(void);

		virtual void	execute(Bureaucrat const &) const;
};

#endif
