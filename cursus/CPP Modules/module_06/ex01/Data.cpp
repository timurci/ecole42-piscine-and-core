#include "Data.hpp"

Data::Data(void) : x(0), octet(0)
{}

Data::Data(const Data &other)
{*this = other;}

Data::Data(int x) : x(x), octet(0)
{}

Data::Data(int x, int octet) : x(x), octet(octet)
{}

Data::~Data(void)
{}

Data	&Data::operator=(const Data &other)
{
	x = other.x;
	octet = other.octet;
	return (*this);
}

int	Data::getX(void) const
{return (x);}

int	Data::getOctet(void) const
{return (octet);}

std::ostream	&operator<<(std::ostream &out, const Data &d)
{
	out << d.getX() << " and " << d.getOctet();
	return (out);
}
