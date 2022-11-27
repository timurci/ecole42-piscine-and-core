#include "Converter.hpp"

Converter::Converter(void) :
	type(INVALID), c(0), i(0), f(0), d(0)
{
}

Converter::Converter(const Converter &other)
{
	*this = other;
}

Converter::Converter(const std::string &in) :
	input(in), c(0), i(0), f(0), d(0)
{
	type = findType();
	if (type != INVALID)
	{
		convertChar(void);
		convertInt(void);
		convertFloat(void);
		convertDouble(void);
	}
}

Converter::~Converter(void)
{
}

Converter	&Converter::operator=(const Converter &other)
{
	input = other.input;
	type = other.type;
	c = other.c;
	i = other.i;
	f = other.f;
	d = other.d;
	return (*this);
}

Converter::e_type	Converter::findType(void) const
{
	if (input.size() == 1
}
