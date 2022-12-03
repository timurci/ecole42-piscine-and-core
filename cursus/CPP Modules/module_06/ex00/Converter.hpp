#ifndef CONVERTER_HPP
# define CONVERTER_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <cctype>
# include <cmath>
# include <exception>
# include <limits>
# include <iomanip>

class	Converter
{
	private:
		std::string		input;
		//e_type			type;
		char			c;
		int				i;
		float			f;
		double			d;
		bool			c_possible;
		bool			i_possible;
		bool			f_possible;
		bool			d_possible;

		void			convertType(void);
		void			convertChar(void);
		void			convertInt(void);
		void			convertFloat(void);
		void			convertDouble(void);

	public:
		Converter(void);
		Converter(const Converter &);
		Converter(const std::string &);
		~Converter(void);

		Converter	&operator=(const Converter &);

		void		printChar(void) const;
		void		printInt(void) const;
		void		printFloat(void) const;
		void		printDouble(void) const;
		void		printAll(void) const;
};

//enum	Converter::e_type
//{
//	INVALID,
//	CHAR,
//	INT,
//	FLOAT,
//	DOUBLE
//};

#endif
