#ifndef SPAN_HPP
# define SPAN_HPP

//# include <exception>
# include <stdexcept>
# include <algorithm>
# include <vector>

class	Span
{
	private:
		typedef std::vector<int>::iterator	int_itr;
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
		void	addNumber(int_itr begin, int_itr end);
		int		shortestSpan(void) const;
		int		longestSpan(void) const;
};

#endif
