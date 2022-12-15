#include "Span.hpp"
#include <iostream>

void	print_elements(const std::vector<int> &v)
{
	std::vector<int>::iterator	itr = v.begin();
	std::vector<int>::iterator	end = v.end();
	size_t						count = 0;

	while (itr != end)
	{
		std::cout << *(itr++) << "\t";
	}
}

int	main(void)
{	
	Span	sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	return 0;
}
