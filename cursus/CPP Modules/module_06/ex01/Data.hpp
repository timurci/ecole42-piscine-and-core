#ifndef DATA_HPP
# define DATA_HPP

# include <iostream>

class	Data
{
	private:
		int	x;
		int	octet;

	public:
		Data(void);
		Data(const Data &);
		Data(int);
		Data(int, int);
		~Data(void);

		Data	&operator=(const Data &);
		
		int		getX(void) const;
		int		getOctet(void) const;
};

std::ostream	&operator<<(std::ostream &, const Data &);

#endif
