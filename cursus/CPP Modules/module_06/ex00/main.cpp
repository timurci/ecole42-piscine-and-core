#include <iostream>
#include <string>
#include "Converter.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{std::cout << "Incorrect number of arguments." << std::endl; return (1);}
	std::string	input(argv[1]);

	Converter	conv(input);

	conv.printAll();
	return (0);
}
