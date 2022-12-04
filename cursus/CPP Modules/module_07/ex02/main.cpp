#include <iostream>
#include "Array.hpp"
#include "Array.tpp"

int	main(void)
{
	Array<int>	x;
	Array<int>	y(5);
	Array<int>	z(y);

	std::cout << "x : " << x.size() << std::endl;
	std::cout << "y : " << y.size() << std::endl;
	x = y;
	std::cout << "-----x=y-----" << std::endl;
	std::cout << "x : " << x.size() << std::endl;
	std::cout << "z : " << z.size() << std::endl;
	std::cout << "Accessing x[50]" << std::endl;
	std::cout << x[50] << std::endl;
}
