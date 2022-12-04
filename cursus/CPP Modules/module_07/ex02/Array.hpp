#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>

template <typename T>
class	Array
{
	private:
		T				*array;
		unsigned int	array_size;

	public:
		Array<T>(void);
		Array<T>(unsigned int);
		Array<T>(const Array<T> &);
		~Array<T>(void);
		
		Array<T>		&operator=(const Array<T> &);
		T				&operator[](const unsigned int i) const;

		unsigned int	size(void) const;
};

#endif
