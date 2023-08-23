#include "PmergeMe.hpp"

template <typename T>
void	printStuff(const T &dq, const char *tag)
{
	typename T::const_iterator	itr = dq.begin();
	typename T::const_iterator	end = dq.end();

	if (tag)
		std::cout << tag << " : ";
	else
		std::cout << "Sort : ";
	for (; itr != end; itr++)
	{
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
}

void	printArgs(char **argv)
{
	std::cout << "Args  : ";
	while (*argv)
	{
		std::cout << *argv << " ";
		argv++;
	}
	std::cout << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);

	++argv;
	PmergeMe	x(argv);
	std::deque<int>	*dq = x.sortQueue();
	std::list<int>	*lst = x.sortList();
	if (dq && lst)
	{
		printArgs(argv);
		printStuff(*dq, "Queue");
		printStuff(*lst, "List ");
		delete dq;
		delete lst;
	}
	return (0);
}
