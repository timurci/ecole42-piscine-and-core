#include "Form.hpp"
#include "Bureaucrat.hpp"

int	main(void)
{
	Bureaucrat	b1("Cemil");
	Form		f1("Food & Drug Regulation", 20, 5);

	std::cout << b1 << std::endl;
	std::cout << f1 << std::endl;
	b1.signForm(f1);
	b1.incGrade(130);
	std::cout << b1 << std::endl;
	b1.signForm(f1);
	b1.signForm(f1);

	return (0);
}
