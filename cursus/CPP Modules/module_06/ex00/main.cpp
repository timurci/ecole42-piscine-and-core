#include <iostream>
#include <string>
#include <ctype>

void	print_int(const std::string &input)
{

}

void	print_char(const std::string &input)
{
	std::cout << "char: ";
	if (input.size() == 1)
	{
		if (isgraph(*input.c_str()))
			std::cout << input;
		else
			std::cout << "Non displayable";
	}
	else
		std::cout << "impossible";
	std::cout << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{std::cout << "Incorrect number of arguments." << std::endl; return (1);}

	std::string	input(argv[1]);

	print_char(input);
	
	return (0);
}
