#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
:	AForm("Shrubbery Creation", 145, 137), target(target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{std::cout << "ShrubberyCreationForm destructor called" << std::endl;}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	checkExecGrade(executor);
	checkIfSigned();
	std::fstream	fs((target + "_shrubbery").c_str(), std::fstream::out);
	fs << "lorem" << std::endl;
	fs << "├── ipsum" << std::endl;
	fs << "│   └── dolor" << std::endl;
	fs << "├── sit" << std::endl;
	fs << "└── amet" << std::endl;
	fs << std::endl
		<< "\
			the\n\
			├── quick\n\
			│   └── brown\n\
			├── fox\n\
			├── jumps\n\
			│  	├── over\n\
			│   │   └── the\n\
			│   └── lazy\n\
			└── dog" << std::endl;
	fs.close();
}
