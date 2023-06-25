#include "BitcoinExchange.hpp"

//------------------------------------------------------------------

BitcoinExchange::BitcoinExchange(void) :
	dbase_file_path(DBASE_FILE_PATH)
{initDbase();}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{*this = other;}

BitcoinExchange::BitcoinExchange(const char *parse_filename) :
	dbase_file_path(DBASE_FILE_PATH)
{initDbase(); parse_file_path = parse_filename;}

BitcoinExchange::BitcoinExchange(const std::string &parse_filename):
	dbase_file_path(DBASE_FILE_PATH)
{initDbase(); parse_file_path = parse_filename;}

BitcoinExchange::~BitcoinExchange(void)
{}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	dbase_file_path = other.dbase_file_path;
	parse_file_path = other.parse_file_path;
	dbase = other.dbase;
	return (*this);
}

//------------------------------------------------------------------

float	BitcoinExchange::findValue(const std::string &date) const
{return (findValue(convDate(date)));}

float	BitcoinExchange::convValue(const std::string &date,
		const float src_value) const
{return (src_value * findValue(date));}

float	BitcoinExchange::convValue(const t_date_value &date,
		const float src_value) const
{return (src_value * findValue(date));}

void	BitcoinExchange::convFile(void) const
{convFile(parse_file_path);}

void	BitcoinExchange::setFile(const std::string parse_filename)
{parse_file_path = parse_filename;}

//------------------------------------------------------------------

float	BitcoinExchange::findValue(const t_date_value &date) const
{
	std::vector<t_date_value>::const_iterator	itr = dbase.begin();
	std::vector<t_date_value>::const_iterator	end = dbase.end();
	std::vector<t_date_value>::const_iterator	pivot = end;

	while (itr != end)
	{
		if (*itr <= date)
			pivot = itr;
		++itr;
	}
	if (pivot == end)
		return (-1);
	return (pivot->cost);
}

BitcoinExchange::t_date_value
	BitcoinExchange::convDate(const std::string &date) const
{
	static int			xx = 0;
	t_date_value		dvalue = {};
	unsigned char		itr = 0;
	std::istringstream	iss(date);
	std::string			field;

	++xx;

	while (std::getline(iss, field, '-'))
	{
		++itr;
		if (itr == 1)
			dvalue.year = atoi(field.c_str());
		if (itr == 2)
			dvalue.month = atoi(field.c_str());
		if (itr == 3)
			dvalue.day = atoi(field.c_str());
	}
	return (dvalue);
}

void	BitcoinExchange::convFile(const std::string &filename) const
{
	std::ifstream	ifp(filename.c_str());

	if (!ifp.is_open())
	{
		std::cerr << "Error: cannot open file " << filename << std::endl;
		std::exit(2);
	}
	
	std::string			line;
	size_t				itr = 0;
	t_date_value		dvalue;
	float				result;

	std::getline(ifp, line);
	while (std::getline(ifp, line))
	{
		++itr;
		dvalue = parseLine(line, '|');
		if (!isValidDate(dvalue) || !isValidValue(dvalue))
			;
		else
		{
			result = convValue(dvalue, dvalue.cost);
			if (result < 0)
				std::cerr << "Error: not a positive number. => " << result << " " << dvalue.cost << std::endl;
			else
				std::cout << dvalue << " = " << result << std::endl;
		}
	}
	ifp.close();
}

BitcoinExchange::t_date_value
	BitcoinExchange::parseLine(const std::string &line, const char delim) const
{
	std::string			field[2];
	std::istringstream	iss(line);
	unsigned char		inner_itr = 0;
	t_date_value		dvalue = {};
	
	while (inner_itr < 3 && std::getline(iss, field[inner_itr], delim))
	{
		++inner_itr;
		if (inner_itr == 1)
			dvalue = convDate(field[0]);
		else if (inner_itr == 2)
			dvalue.cost = atof(field[1].c_str());
	}
	if (inner_itr != 2 || (!isValidDate(dvalue) && !isValidValue(dvalue)))
		std::cerr << "Error: bad input => " << field[0] << std::endl;
	else if (!isValidDate(dvalue))
		std::cerr << "Error: bad input => " << field[0] << std::endl;
	else if (dvalue.cost < 0)
		std::cerr << "Error: not a positive number." << std::endl;
	else if (!isValidValue(dvalue) && delim == '|')
		std::cerr << "Error: too large a number." << std::endl;
	return (dvalue);
}

void	BitcoinExchange::initDbase(void)
{
	std::ifstream	ifp(dbase_file_path.c_str());

	if (!ifp.is_open())
	{
		std::cerr << "Error: cannot open file " << dbase_file_path << std::endl;
		exit(2);
	}
	
	std::string			line;
	size_t				itr = 0;
	t_date_value		dvalue;

	std::getline(ifp, line);
	while (std::getline(ifp, line))
	{
		++itr;
		dvalue = parseLine(line, ',');
		if (!isValidDate(dvalue) || !isValidValue(dvalue))
			;
		else
			dbase.push_back(dvalue);
	}
	ifp.close();
	std::sort(dbase.begin(), dbase.end());
}

//------------------------------------------------------------------

bool	BitcoinExchange::isValidDate(const t_date_value &dvalue) const
{
	if (dvalue.day == 0 || dvalue.month == 0 || dvalue.year < 1850)
		return (0);
	if (dvalue.day > 31 || dvalue.month > 12 || dvalue.year > 2023)
		return (0);
	return (1);
}

bool	BitcoinExchange::isValidValue(const t_date_value &dvalue) const
{
	if (dvalue.cost < 0 || dvalue.cost > 1000)
		return (0);
	return (1);
}

//------------------------------------------------------------------

void	BitcoinExchange::printItems(const unsigned int n) const
{
	unsigned int												loop = 0;
	std::vector<BitcoinExchange::t_date_value>::const_iterator	itr = dbase.begin();
	std::vector<BitcoinExchange::t_date_value>::const_iterator	end = dbase.end();

	std::cout << "=================================" << std::endl;
	std::cout << "         BitcoinExchange         " << std::endl;
	std::cout << "=================================" << std::endl;
	while(itr != end && loop < n)
	{
		std::cout << itr->year << "-" << itr->month << "-" << itr->day
			<< " => " << itr->cost << std::endl;
		++loop;
		++itr;
	}
	if (loop == n && itr != end)
		std::cout << "..." << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << "Total : " << loop << std::endl;
	std::cout << "=================================" << std::endl;
}

bool	operator<(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2)
{
	if (dv1.year < dv2.year)
		return (true);
	else if (dv1.year == dv2.year && dv1.month < dv2.month)
		return (true);
	else if (dv1.year == dv2.year && dv1.month == dv2.month
			&& dv1.day < dv2.day)
		return (true);
	return (false);
}

bool	operator>(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2)
{
	if (dv1.year > dv2.year)
		return (true);
	else if (dv1.year == dv2.year && dv1.month > dv2.month)
		return (true);
	else if (dv1.year == dv2.year && dv1.month == dv2.month
			&& dv1.day > dv2.day)
		return (true);
	return (false);
}

bool	operator==(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2)
{
	if (dv1.year == dv2.year && dv1.month == dv2.month
		&& dv1.day == dv2.day)
		return (true);
	return (false);
}

bool	operator<=(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2)
{
	return (dv1 < dv2 || dv1 == dv2);
}

bool	operator>=(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2)
{
	return (dv1 > dv2 || dv1 == dv2);
}

std::ostream	&operator<<(std::ostream &os, BitcoinExchange::t_date_value &dv)
{
	os << dv.year << "-" << dv.month << "-" << dv.day
		<< " => " << dv.cost;
	return (os);
}
