#include "iter.hpp"
#include <iostream>
#include <cstring>

void	inc(char &c)
{
	c++;
}

void	dec(char &c)
{
	c--;
}

int	main(void)
{
	char	str[] = "Hello World!";

	iter(str, strlen(str), inc);
	std::cout << str << std::endl;
	iter(str, strlen(str), dec);
	std::cout << str << std::endl;
}
