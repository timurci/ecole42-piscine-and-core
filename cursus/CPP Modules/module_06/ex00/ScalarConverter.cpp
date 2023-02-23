#include "ScalarConverter.hpp"

char		ScalarConverter::c;
int			ScalarConverter::i;
float		ScalarConverter::f;
double		ScalarConverter::d;
bool		ScalarConverter::c_possible;
bool		ScalarConverter::i_possible;
bool		ScalarConverter::f_possible;
bool		ScalarConverter::d_possible;
std::string	ScalarConverter::input;

ScalarConverter::ScalarConverter(void)
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	*this = other;
}

ScalarConverter::~ScalarConverter(void)
{
}

ScalarConverter	&ScalarConverter::operator=(const ScalarConverter &other)
{
	const ScalarConverter	*p = &other;

	if (p)
		return (*this);
	return (*this);
}

void	ScalarConverter::convertType(void)
{
	long int tmp = atol(input.c_str());
	
	if (input.size() == 0)
		return ;
	else if (input.size() == 1 && !isdigit(*input.c_str()))
		convertChar();
	else if (input.find('f') != std::string::npos
			&& input.compare("-inf") && input.compare("+inf"))
		convertFloat();
	else if (!input.compare("nan") || input.find('f') != std::string::npos
			|| input.find(".") != std::string::npos
			|| tmp >= std::numeric_limits<int>::max()
			|| tmp <= std::numeric_limits<int>::min())
		convertDouble();
	else
		convertInt();
}

void	ScalarConverter::convert(const std::string &input)
{
	ScalarConverter::input = input;
	c = 0;
	i = 0;
	f = 0;
	d = 0;
	c_possible = 0;
	i_possible = 0;
	f_possible = 0;
	d_possible = 0;

	ScalarConverter::convertType();
	ScalarConverter::printAll();
}

void	ScalarConverter::convertChar(void)
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

void	ScalarConverter::convertInt(void)
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

	if (i == 0 || (i >= -std::numeric_limits<float>::max()
			&& i <= std::numeric_limits<float>::max()))
	{f = static_cast<float> (i); f_possible = 1;}

	if (i == 0 || (i >= -std::numeric_limits<double>::max()
			&& i <= std::numeric_limits<double>::max()))
	{d = static_cast<double> (i); d_possible = 1;}
}

void	ScalarConverter::convertFloat(void)
{
	double	tmp = atof(input.c_str());

	if (!input.compare("nanf"))
		f = nanf("");
	else if (!input.compare("+inff"))
		f = std::numeric_limits<float>::infinity();
	else if (!input.compare("-inff"))
		f = -std::numeric_limits<float>::infinity();
	else if (tmp == 0 || (tmp >= -std::numeric_limits<float>::max()
			&& tmp <= std::numeric_limits<float>::max()))
		f = strtof(input.c_str(), NULL);
	else
		return ;
	f_possible = 1;

	if (isnan(f) || isinf(f) || f == 0
		|| (f >= -std::numeric_limits<double>::max()
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

void	ScalarConverter::convertDouble(void)
{
	long double	tmp = strtold(input.c_str(), NULL);

	if (!input.compare("nan"))
		d = nan("");
	else if (!input.compare("+inf"))
		d = std::numeric_limits<double>::infinity();
	else if (!input.compare("-inf"))
		d = -std::numeric_limits<double>::infinity();
	else if (tmp == 0 || (tmp >= -std::numeric_limits<double>::max()
			&& tmp <= std::numeric_limits<double>::max()))
		d = atof(input.c_str());
	else
		return ;
	d_possible = 1;
	
	if (isnan(d) || isinf(d) || d == 0
		|| (d >= -std::numeric_limits<float>::max()
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

void	ScalarConverter::printChar(void)
{
	std::cout << "char: ";
	if (!c_possible)
		std::cout << "impossible";
	else if (!isgraph(c))
		std::cout << "Non displayable";
	else
		std::cout << "'" << c << "'";
	std::cout << std::endl;
}

void	ScalarConverter::printInt(void)
{
	std::cout << "int: ";
	if (!i_possible)
		std::cout << "impossible";
	else
		std::cout << i;
	std::cout << std::endl;
}

void	ScalarConverter::printFloat(void)
{
	std::cout << "float: ";
	if (!f_possible)
		std::cout << "impossible";
	else if (isnan(f))
		std::cout << "nanf";
	else if (isinf(f) && f > 0)
		std::cout << "+inff";
	else if (isinf(f) && f < 0)
		std::cout << "-inff";
	else
		std::cout << std::fixed << std::setprecision(1) << f << "f";
	std::cout << std::endl;
}

void	ScalarConverter::printDouble(void)
{
	std::cout << "double: ";
	if (!d_possible)
		std::cout << "impossible";
	else if (isinf(d) && d > 0)
		std::cout << "+inf";
	else if (isinf(d) && d < 0)
		std::cout << "-inf";
	else
		std::cout << d;
	std::cout << std::endl;
}

void	ScalarConverter::printAll(void)
{
	printChar();
	printInt();
	printFloat();
	printDouble();
}
