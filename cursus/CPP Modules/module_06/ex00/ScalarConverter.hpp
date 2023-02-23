#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <cctype>
# include <cmath>
# include <exception>
# include <limits>
# include <iomanip>

class	ScalarConverter
{
	private:
		static std::string	input;
		//e_type			type;

		static char			c;
		static int			i;
		static float		f;
		static double		d;
		static bool			c_possible;
		static bool			i_possible;
		static bool			f_possible;
		static bool			d_possible;

		static void			convertType(void);
		static void			convertChar(void);
		static void			convertInt(void);
		static void			convertFloat(void);
		static void			convertDouble(void);

		ScalarConverter(void);
		ScalarConverter(const ScalarConverter &);
		~ScalarConverter(void);

		ScalarConverter	&operator=(const ScalarConverter &);

		static void		printChar(void);
		static void		printInt(void);
		static void		printFloat(void);
		static void		printDouble(void);
		static void		printAll(void);
	
	public:

		static void	convert(const std::string &input);
};


//enum	ScalarConverter::e_type
//{
//	INVALID,
//	CHAR,
//	INT,
//	FLOAT,
//	DOUBLE
//};

#endif
