#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# ifndef DBASE_FILE_PATH
#  define DBASE_FILE_PATH "cpp09/data.csv"
# endif

# include <fstream>
# include <iostream>
# include <utility>
# include <vector>

class BitcoinExchange
{
	private:
		typedef std::pair<std::string, float> t_date_value;
		typedef std::vector<t_date_value> t_bitcoin_dbase;

	private:
		std::string		dbase_file_path;
		std::string		parse_file_path;
		t_bitcoin_dbase	dbase;

		void	initDbase(void);

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange(const char *parse_filename);
		BitcoinExchange(const std::string parse_filename);
		~BitcoinExchange(void);

		BitcoinExchange	&operator=(const BitcoinExchange &);

	public:
		float	findValue(const std::string &date) const;
		float	convValue(const std::string &date, const float src_value) const;
		void	convFile(const std::string &filename) const;

		void	convFile(void) const;
		void	setFile(const std::string parse_filename);

};


#endif
