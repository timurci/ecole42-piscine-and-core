#include "Span.hpp"
#include <iostream>

void	mass_addition(Span &sp, unsigned int gap, size_t size)
{
	std::vector<int>	v;
	unsigned int		num = 0;

	for (size_t i = 0; i < size; i++)
	{
		v.push_back(num);
		num += gap;
	}
	sp.addNumber(v.begin(), v.end());
}

int	main(void)
{	
	Span	sp1 = Span(5);
	int		size = 1000;
	Span	sp2 = Span(size);

	sp1.addNumber(6);
	sp1.addNumber(3);
	sp1.addNumber(17);
	sp1.addNumber(9);
	sp1.addNumber(11);
	std::cout << sp1.shortestSpan() << std::endl;
	std::cout << sp1.longestSpan() << std::endl;
	mass_addition(sp2, 5, size);
	std::cout << sp2.shortestSpan() << std::endl;
	std::cout << sp2.longestSpan() << std::endl;
	return 0;
}
