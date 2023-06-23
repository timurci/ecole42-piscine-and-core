#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

static void	print_readnline(std::fstream &fp, const size_t nline = 10,
		const bool setn = false)
{
	std::string		line;
	size_t			itr = 0;

	for (; fp.good() && itr < nline; getline(fp, line))
	{
		++itr;
		if (setn)
			std::cout << itr << "\t| " << line << std::endl;
		else
			std::cout << line << std::endl;
	}
}

int	main(int argc, char **argv)
{
	std::fstream	fp;

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
	fp.open(argv[1], std::ios::in);
	if (!fp.is_open())
	{
		std::cerr << "Error: cannot open file " << argv[1] << std::endl;
		return (3);
	}
	
	print_readnline(fp, 10, 1);

	if (fp.eof())
		std::cerr << "eof\n";
	if (fp.fail())
		std::cerr << "fail\n";
	if (fp.bad())
		std::cerr << "bad\n";

	fp.close();
	return (0);
}
