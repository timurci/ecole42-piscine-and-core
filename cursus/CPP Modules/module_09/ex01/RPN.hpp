#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <cctype>
# include <stack>
# include <iostream>

class	RPN
{
	private:
		std::string	exprs;

		bool	isOperator(const unsigned char n) const;
		bool	useOperator(std::stack<float> &numStack,
					const unsigned char n) const;

	public:
		RPN(void);
		RPN(const RPN &);
		RPN(const std::string &);
		RPN(const char *);
		~RPN(void);

		RPN	&operator=(const RPN &);

		void	setExprs(const std::string &);

		void	solveExprs(void) const;
		void	solveExprs(const std::string &);
};

#endif