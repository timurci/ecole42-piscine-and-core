#include <iostream>
#include <string>
#include "ScalarConverter.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{std::cout << "Incorrect number of arguments." << std::endl; return (1);}
	std::string	input(argv[1]);

	//ScalarConverter	conv(input);
	//conv.printAll();
	
	ScalarConverter::convert(input);
	return (0);
}
