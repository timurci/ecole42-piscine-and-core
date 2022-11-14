#ifndef SHRUBBERY_CREATION_FORM
# define SHRUBBERY_CREATION_FORM

# include "Form.hpp"
# include "Bureaucrat.hpp"
# include <fstream>

class ShrubberyCreationForm : public Form
{
	private:
		std::string	target;

	public:
		ShrubberyCreationForm(std::string);
		~ShrubberyCreationForm(void);

		virtual void	execute(Bureaucrat const &) const;
};

#endif
