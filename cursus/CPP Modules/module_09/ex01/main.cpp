#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc > 2)
	{std::cout << "Error: Too many arguments." << std::endl; return (1);}
	else if (argc == 1)
	{std::cout << "Error: Incomplete argument." << std::endl; return(1);}

	RPN			rpn(argv[1]);

	rpn.solveExprs();
	return (0);
}
