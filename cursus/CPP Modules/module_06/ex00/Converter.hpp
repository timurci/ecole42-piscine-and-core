#ifndef CONVERTER_HPP
# define CONVERTER_HPP

# include <iostream>
# include <string>

class	Converter
{
	private:
		enum			e_type;

		std::string		input;
		e_type			type;
		char			c;
		int				i;
		float			f;
		double			d;

		e_type			findType(void) const;
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
};

enum	Converter::literal_type
{
	INVALID,
	CHAR,
	INT,
	FLOAT,
	DOUBLE
};

#endif
