#ifndef ROBOTOMY_REQUEST_FORM
# define ROBOTOMY_REQUEST_FORM

# include "Form.hpp"
# include "Bureaucrat.hpp"
# include <cstdlib>

class RobotomyRequestForm : public Form
{
	private:
		std::string	target;

	public:
		RobotomyRequestForm(std::string);
		~RobotomyRequestForm(void);

		virtual void	execute(Bureaucrat const &) const;
};

#endif
