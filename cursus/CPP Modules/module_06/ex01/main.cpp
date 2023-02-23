#include <iostream>
#include <stdint.h>
#include "Data.hpp"
#include "Serializer.hpp"

int	main(void)
{
	Data	d1(4,5);
	Data	d2(81);
	Data	d3;

	d3 = d2;
	d2 = Data(150, 15);

	std::cout << "d1 : " << d1 << std::endl;
	std::cout << "d2 : " << d2 << std::endl;
	std::cout << "d3 : " << d3 << std::endl;

	Data		*dp;
	uintptr_t	raw;

	dp = &d1;
	std::cout << "*dp: " << *dp << std::endl;
	std::cout << "dp : " << dp << std::endl;
	raw = Serializer::serialize(dp);
	std::cout << "----serialize----" << std::endl << "raw: " << raw << std::endl;
	dp = Serializer::deserialize(raw);
	std::cout << "---deserialize---" << std::endl << "dp : " << dp << std::endl;
}
