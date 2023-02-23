#include "Serializer.hpp"

Serializer::Serializer(void)
{}

Serializer::Serializer(const Serializer &other)
{*this = other;}

Serializer::~Serializer(void)
{}

Serializer	&Serializer::operator=(const Serializer &other)
{
	const Serializer	*p = &other;

	if (p)
		return (*this);
	return (*this);
}

uintptr_t	Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t> (ptr));
}

Data	*Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*> (raw));
}
