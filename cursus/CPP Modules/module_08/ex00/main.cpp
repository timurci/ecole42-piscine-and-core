#include "easyfind.hpp"
#include "easyfind.tpp"
#include <iostream>
#include <vector>
#include <exception>

int	main(void)
{
	std::vector<int>	x;

	x.push_back(5);
	x.push_back(87);
	x.push_back(-12);
	x.push_back(49);

	std::cout << easyfind(x, 87) << std::endl;
	std::cout << easyfind(x, -12) << std::endl;
	try
	{std::cout << easyfind(x, 56) << std::endl;}
	catch(std::exception &exc)
	{std::cout << "Exception thrown: " << exc.what() << std::endl;}
}
