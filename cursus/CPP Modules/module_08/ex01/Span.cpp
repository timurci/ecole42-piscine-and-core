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
