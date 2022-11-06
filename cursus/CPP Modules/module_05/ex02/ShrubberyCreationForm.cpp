#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
:	Form("Shrubbery Creation", 145, 137), target(target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{std::cout << "ShrubberyCreationForm destructor called" << std::endl;}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	checkExecGrade(executor);
	checkIsSigned();
	std::fstream	fs((target + "_shrubbery").c_str(), std::fstream::out);
	fs << "lorem" << std::endl;
	fs << "├── ipsum" << std::endl;
	fs << "│   └── dolor" << std::endl;
	fs << "├── sit" << std::endl;
	fs << "└── amet" << std::endl;
	fs << std::endl
		<< "\
			the\
			├── quick\
			│   └── brown\
			├── fox\
			├── jumps\
			│  	├── over\
			│   │   └── the\
			│   └── lazy\
			└── dog" << std::endl;
	fs.close();
}
