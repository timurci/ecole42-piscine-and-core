#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	BitcoinExchange	bx;

	//bx.printItems(10);

	if (argc < 2)
	{
		std::cerr << "Error: filename missing." << std::endl;
		return (1);
	}
	if (argc > 2)
	{
		std::cerr << "Error: too many arguments." << std::endl;
		return (2);
	}

	bx.convFile(argv[1]);

	return (0);
}
