#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);

	PmergeMe	x(++argv);
	std::deque<int>	*dq = x.sortQueue();
	return (0);
}
