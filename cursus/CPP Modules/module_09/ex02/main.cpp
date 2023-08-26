#include           "PmergeMe.hpp"
#include           <ctime>
#include           <iomanip>
#include           <unistd.h>
#define  RESET     "\033[0m"
#define  RED       "\033[31m"
#define  GREEN     "\033[32m"
#define  BOLDRED   "\033[1m\033[31m"
#define  BOLDGREEN "\033[1m\033[32m"

template <typename T>
void	printStuff(const T &dq, const char *tag)
{
	typename T::const_iterator	itr = dq.begin();
	typename T::const_iterator	end = dq.end();

	std::cout << BOLDGREEN;

	if (tag)
		std::cout << "[ " << tag << " ]";
	else
		std::cout << "[ " << "Sort" << " ]";
	
	std::cout << std::endl << RESET;

	for (; itr != end; itr++)
	{
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
}

void	printArgs(char **argv)
{
	std::cout << BOLDRED;
	std::cout << "[ " << "Args" << " ]";
	std::cout << std::endl << RESET;
	while (*argv)
	{
		std::cout << *argv << " ";
		argv++;
	}
	std::cout << std::endl;
}

void	printTime(const std::string &name, int size,
		const clock_t &start, const clock_t &end)
{
std::cout << "Time to process a range of " << size
	<< " elements with " << name << " is " << std::fixed
	<< std::setprecision(20) << (double) (end - start) / CLOCKS_PER_SEC;
std::cout << " sec " << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);

	clock_t	tpoint[3];

	++argv;
	PmergeMe	x(argv);
	tpoint[0] = clock();
	std::deque<int>	*dq = x.sortQueue();
	tpoint[1] = clock();
	std::list<int>	*lst = x.sortList();
	tpoint[2] = clock();
	if (dq && lst)
	{
		printArgs(argv);
		std::cout << std::endl;
		printStuff(*dq, "Queue");
		std::cout << std::endl;
		printStuff(*lst, "List");
		std::cout << std::endl;
		printTime("std::deque", argc - 1, tpoint[0], tpoint[1]);
		printTime("std::list ", argc - 1, tpoint[1], tpoint[2]);
		delete dq;
		delete lst;
	}
	return (0);
}
