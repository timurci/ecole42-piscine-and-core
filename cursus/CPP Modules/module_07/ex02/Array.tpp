#include "Array.hpp"

template <typename T>
Array<T>::Array(void) : array(new T[1]), array_size(1)
{}

template <typename T>
Array<T>::Array(unsigned int n) : array(new T[n]), array_size(n)
{}

template <typename T>
Array<T>::Array(const Array<T> &other) : array_size(0)
{*this = other;}

template <typename T>
Array<T>::~Array(void)
{
	if (array_size && array)
		delete[] array;
}

template <typename T>
Array<T>	&Array<T>::operator=(const Array<T> &other)
{
	if (array_size)
		delete[] array;
	array = NULL;
	array_size = 0;
	array = new T[other.array_size];
	array_size = other.array_size;
	for (unsigned int i = 0; i < array_size; i++)
		array[i] = other.array[i];
	return (*this);
}

template <typename T>
T	&Array<T>::operator[](const unsigned int i) const
{
	if (i >= array_size)
		throw std::out_of_range("Out of range!!!!");
	return (array[i]);
}

template <typename T>
unsigned int	Array<T>::size(void) const
{return (array_size);}
