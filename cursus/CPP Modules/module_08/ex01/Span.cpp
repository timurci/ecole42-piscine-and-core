#include "Span.hpp"

Span::Span(void) : max_size(0)
{}

Span::Span(const Span &other) : max_size(other.max_size)
{
	*this = other;
}

Span::Span(int N) : max_size(N)
{}

Span::~Span(void)
{}

Span	&Span::operator=(const Span &other)
{
	if (max_size < other.arr.size())
		throw std::out_of_range("Assigned array size is too big");
	arr = other.arr;
	return (*this);
}

void	Span::addNumber(int n)
{
	if (arr.size() == max_size)
		throw std::out_of_range("Array is full");
	arr.push_back(n);
}

void	Span::addNumber(Span::int_itr begin, Span::int_itr end)
{
	if (arr.size() + std::distance(begin, end) > max_size)
		throw std::out_of_range("Range of iterators is too big");
	arr.insert(arr.end(), begin, end);
}

int	Span::shortestSpan(void) const
{
	std::vector<int>	v_copy = arr;

	std::sort(v_copy.begin(), v_copy.end());
	
	std::vector<int>::iterator	itr = v_copy.begin();
	std::vector<int>::iterator	pivot;
	std::vector<int>::iterator	end = v_copy.end();
	int							dif = longestSpan();
	
	while (itr != end - 1)
	{
		pivot = itr++;
		if (*itr - *pivot < dif)
			dif = *itr - *pivot;
	}
	return (dif);
}

int	Span::longestSpan(void) const
{
	std::vector<int>::const_iterator	itr = arr.begin();
	std::vector<int>::const_iterator	end = arr.end();

	return (*std::max_element(itr, end) - *std::min_element(itr, end));
}
