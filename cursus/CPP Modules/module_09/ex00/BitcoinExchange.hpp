#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <ostream>
# ifndef DBASE_FILE_PATH
#  define DBASE_FILE_PATH "cpp_09/data.csv"
# endif

# include <fstream>
# include <iostream>
# include <utility>
# include <vector>
# include <string>
# include <sstream>
# include <cstdlib>
# include <algorithm>

class BitcoinExchange
{
	public:
		struct	s_date_value;
		typedef s_date_value t_date_value;
		typedef std::vector<t_date_value> t_bitcoin_dbase;

	private:
		std::string		dbase_file_path;
		std::string		parse_file_path;
		t_bitcoin_dbase	dbase;

		void			initDbase(void);
		t_date_value	convDate(const std::string &date) const;
		t_date_value	parseLine(const std::string &line, const char delim) const;
		float			convValue(const t_date_value &date,
						const float src_value) const;
		bool			isValidDate(const t_date_value &dvalue) const;
		bool			isValidValue(const t_date_value &dvalue) const;

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange(const char *parse_filename);
		BitcoinExchange(const std::string &parse_filename);
		~BitcoinExchange(void);

		BitcoinExchange	&operator=(const BitcoinExchange &);

	public:
		float	findValue(const std::string &date) const;
		float	findValue(const t_date_value &date) const;
		float	convValue(const std::string &date, const float src_value) const;
		void	convFile(const std::string &filename) const;

		void	convFile(void) const;
		void	setFile(const std::string parse_filename);

		void	printItems(const unsigned int n) const;
		
};

struct BitcoinExchange::s_date_value
{
	unsigned short	year;
	unsigned short	month;
	unsigned short	day;
	float			cost;
};

bool	operator<(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2);

bool	operator>(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2);

bool	operator==(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2);

bool	operator<=(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2);

bool	operator>=(
		const BitcoinExchange::t_date_value &dv1,
		const BitcoinExchange::t_date_value &dv2);

std::ostream	&operator<<(std::ostream &os, BitcoinExchange::t_date_value &dv);

#endif
