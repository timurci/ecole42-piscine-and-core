#ifndef SPAN_HPP
# define SPAN_HPP

//# include <exception>
# include <stdexcept>
# include <vector>

class	Span
{
	private:
		std::vector<int>						arr;
		const std::vector<int>::size_type		max_size;

	public:
		Span(void);
		Span(const Span &);
		Span(int);
		~Span(void);

		Span	&operator=(const Span &);
		void	addNumber(int);
		void	addManyNumbers(int, int);
};

#endif
