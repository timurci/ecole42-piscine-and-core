#include "RPN.hpp"

RPN::RPN(void)
{}

RPN::RPN(const RPN &other)
{*this = other;}

RPN::RPN(const std::string &str) : exprs(str)
{}

RPN::RPN(const char *str) : exprs(str)
{}

RPN::~RPN(void)
{}

RPN	&RPN::operator=(const RPN &other)
{
	exprs = other.exprs;
	return (*this);
}

void	RPN::setExprs(const std::string &str)
{exprs = str;}

void	RPN::solveExprs(void) const
{
	if (exprs.length() == 0)
	{std::cout << "Error: Empty expression." << std::endl; return;}
	
	std::stack<float>			numStack;
	std::string::const_iterator	itr = exprs.begin();
	std::string::const_iterator	end = exprs.end();

	for (; itr != end; itr++)
	{
		if (isspace(*itr))
			;
		else if (*itr > '0' && *itr <= '9')
			numStack.push(*itr - '0');
		else if (isOperator(*itr))
		{
			if (!useOperator(numStack, *itr))
			   return ;
		}
		else
		{std::cout << "Error: Syntax error." << std::endl; return;}
	}
	if (numStack.size() > 1)
		std::cout << "Error: Incomplete operators." << std::endl;
	else if (numStack.size() == 0)
		std::cout << "Error: No number in expression." << std::endl;
	else
		std::cout << numStack.top() << std::endl;
}

void	RPN::solveExprs(const std::string &str)
{
	exprs = str;
	this->solveExprs();
}

bool	RPN::isOperator(const unsigned char c) const
{
	if (c == '+')
		return (true);
	if (c == '-')
		return (true);
	if (c == '*')
		return (true);
	if (c == '/')
		return (true);
	return (false);
}

bool	RPN::useOperator(std::stack<float> &numStack,
			const unsigned char opr) const
{
	float	num1;
	float	num2;

	if (numStack.size() < 2)
	{std::cout << "Error: Too many operators." << std::endl; return (false);}
	num2 = numStack.top();
	numStack.pop();
	num1 = numStack.top();
	numStack.pop();
	if (opr == '+')
		num1 += num2;
	else if (opr == '-')
		num1 -= num2;
	else if (opr == '*')
		num1 *= num2;
	else if (opr == '/' && num2 != 0)
		num1 /= num2;
	else
	{std::cout << "Error: Division by zero." << std::endl; return (false);}
	numStack.push(num1);
	return (true);
}
