#define "BitcoinExchange.hpp"

//------------------------------------------------------------------

BitcoinExchange::BitcoinExchange(void)
{initDbase();}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{*this = other;}

BitcoinExchange::BitcoinExchange(const char *parse_filename)
{initDbase(); parse_file_path = parse_filename;}

BitcoinExchange::BitcoinExchange(const std::string &parse_filename)
{initDbase(); parse_file_path = parse_filename;}

BitcoinExchange::~BitcoinExchange(void)
{}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	dbase_file_path = other.dbase_file_path;
	parse_file_path = other.parse_file_path;
	dbase = other.dbase;
}

//------------------------------------------------------------------


float	BitcoinExchange::convValue(const std::string &date,
		const float src_value) const
{return (src_value * );}

//------------------------------------------------------------------

void	BitcoinExchange::convFile(void) const
{convFile(parse_file_path);}

void	BitcoinExchange::setFile(const std::string parse_filename)
{parse_file_path = parse_filename;}

//------------------------------------------------------------------
//------------------------------------------------------------------

