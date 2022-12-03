#include "Converter.hpp"

Converter::Converter(void) :
	c(0), i(0), f(0), d(0),
	c_possible(0), i_possible(0), f_possible(0), d_possible(0)
{
}

Converter::Converter(const Converter &other)
{
	*this = other;
}

Converter::Converter(const std::string &in) :
	input(in), c(0), i(0), f(0), d(0),
	c_possible(0), i_possible(0), f_possible(0), d_possible(0)
{
	convertType();
}

Converter::~Converter(void)
{
}

Converter	&Converter::operator=(const Converter &other)
{
	input = other.input;
	c = other.c;
	i = other.i;
	f = other.f;
	d = other.d;
	c_possible = other.c_possible;
	i_possible = other.i_possible;
	f_possible = other.f_possible;
	d_possible = other.d_possible;
	return (*this);
}

void	Converter::convertType(void)
{
	if (input.size() == 0)
		return ;
	else if (input.size() == 1 && !isdigit(*input.c_str()))
		convertChar();
	else if (input.find('f') != std::string::npos
			&& input.compare("-inf") && input.compare("+inf"))
		convertFloat();
	else if (!input.compare("nan") || input.find('f') != std::string::npos
			|| input.find(".") != std::string::npos)
		convertDouble();
	else
		convertInt();
}

void	Converter::convertChar(void)
{
	c = *input.c_str();
	i = static_cast<int> (c);
	f = static_cast<float> (c);
	d = static_cast<double> (c);
	c_possible = 1;
	i_possible = 1;
	f_possible = 1;
	d_possible = 1;
}

void	Converter::convertInt(void)
{
	long int tmp = atol(input.c_str());

	if (tmp >= std::numeric_limits<int>::min()
		&& tmp <= std::numeric_limits<int>::max())
		i = std::atoi(input.c_str());
	else
		return ;
	i_possible = 1;

	if (i >= std::numeric_limits<char>::min()
		&& i <= std::numeric_limits<char>::max())
	{c = static_cast<char> (i); c_possible = 1;}

	if (i == 0 || (i >= std::numeric_limits<float>::min()
			&& i <= std::numeric_limits<float>::max()))
	{f = static_cast<float> (i); f_possible = 1;}

	if (i == 0 || (i >= std::numeric_limits<double>::min()
			&& i <= std::numeric_limits<double>::max()))
	{d = static_cast<double> (i); d_possible = 1;}
}

void	Converter::convertFloat(void)
{
	double	tmp = atof(input.c_str());

	if (!input.compare("nanf"))
		f = nanf("");
	else if (!input.compare("+inff"))
		f = std::numeric_limits<float>::infinity();
	else if (!input.compare("-inff"))
		f = -std::numeric_limits<float>::infinity();
	else if (tmp == 0 || (tmp >= std::numeric_limits<float>::min()
			&& tmp <= std::numeric_limits<float>::max()))
		f = strtof(input.c_str(), NULL);
	else
		return ;
	f_possible = 1;

	if (isnan(f) || isinf(f) || f == 0
		|| (f >= std::numeric_limits<double>::min()
			&& f <= std::numeric_limits<double>::max()))
	{d = static_cast<double> (f); d_possible = 1;}
	
	if (isnan(f) || isinf(f))
		return ;

	if (f >= std::numeric_limits<char>::min()
		&& f <= std::numeric_limits<char>::max())
	{c = static_cast<char> (f); c_possible = 1;}
	
	if (f >= std::numeric_limits<int>::min()
		&& f <= std::numeric_limits<int>::max())
	{i = static_cast<int> (f); i_possible = 1;}
}

void	Converter::convertDouble(void)
{
	long double	tmp = strtold(input.c_str(), NULL);

	if (!input.compare("nan"))
		d = nan("");
	else if (!input.compare("+inf"))
		d = std::numeric_limits<double>::infinity();
	else if (!input.compare("-inf"))
		d = -std::numeric_limits<double>::infinity();
	else if (tmp == 0 || (tmp >= std::numeric_limits<double>::min()
			&& tmp <= std::numeric_limits<double>::max()))
		d = atof(input.c_str());
	else
		return ;
	d_possible = 1;
	
	if (isnan(d) || isinf(d) || d == 0
		|| (d >= std::numeric_limits<float>::min()
			&& d <= std::numeric_limits<float>::max()))
	{f = static_cast<float> (d); f_possible = 1;}

	if (isnan(d) || isinf(d))
		return ;
	
	if (d >= std::numeric_limits<char>::min()
		&& d <= std::numeric_limits<char>::max())
	{c = static_cast<char> (d); c_possible = 1;}
	
	if (d >= std::numeric_limits<int>::min()
		&& d <= std::numeric_limits<int>::max())
	{i = static_cast<int> (d); i_possible = 1;}
}

void	Converter::printChar(void) const
{
	std::cout << "char: ";
	if (!c_possible)
		std::cout << "impossible";
	else if (!isgraph(c))
		std::cout << "Non displayable";
	else
		std::cout << c;
	std::cout << std::endl;
}

void	Converter::printInt(void) const
{
	std::cout << "int: ";
	if (!i_possible)
		std::cout << "impossible";
	else
		std::cout << i;
	std::cout << std::endl;
}

void	Converter::printFloat(void) const
{
	std::cout << "float: ";
	if (!f_possible)
		std::cout << "impossible";
	else if (isnan(f))
		std::cout << "nanf";
	else if (isinf(f) > 0)
		std::cout << "+inff";
	else if (isinf(f) < 0)
		std::cout << "-inff";
	else
		std::cout << std::fixed << std::setprecision(1) << f << "f";
	std::cout << std::endl;
}

void	Converter::printDouble(void) const
{
	std::cout << "double: ";
	if (!d_possible)
		std::cout << "impossible";
	else
		std::cout << d;
	std::cout << std::endl;
}

void	Converter::printAll(void) const
{
	printChar();
	printInt();
	printFloat();
	printDouble();
}
