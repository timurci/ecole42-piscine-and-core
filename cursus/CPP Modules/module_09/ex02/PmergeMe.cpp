#include "PmergeMe.hpp"

// Constructors & Destructors & Operators

PmergeMe::PmergeMe(void) : args(NULL), nums(NULL), nums_size(0)
{}


PmergeMe::PmergeMe(char **args)
{
	setArgs(args);
}

PmergeMe::PmergeMe(const PmergeMe &other)
{*this = other;}

PmergeMe::~PmergeMe(void)
{
	if (nums)
		delete[] nums;
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other)
{
	args = other.args;
	nums = other.nums;
	nums_size = ohter.nums_size;
}

// setArgs & checkArgs

bool	PmergeMe::setArgs(char **new_args)
{
	size_t	size = 0;

	while (new_args[size])
	{
		size++;
		if (!strlen(new_args[size]))
		{
			size = 0;
			break ;
		}
	}
	
	if (!size)
	{
		std::cerr << "Error: There is an empty argument." << std::endl;
		return (false);
	}

	int		*new_nums = new int[size];

	for (size_t itr = 0; itr < size; itr++)
		new_nums[itr] = atoi(new_args[itr]);
	if (checkArgs(new_nums, size))
	{
		if (nums)
			delete[] nums;
		nums = new_nums;
		args = new_args;
		nums_size = size;
	}
	else
	{
		delete[] new_nums;
		std::cerr << "Error: Invalid args." << std::endl;
		return (false);
	}
	return (true);
}

bool	PmergeMe::checkArgs(const int *src, const size_t src_size) const
{
	for (size_t i = 0; i < src_size; i++)
	{
		if (src < 0)
			return (false);
	}
	return (true);
}

// Sort Args

std::deque<int>	*PmergeMe::sortQueue(char **args);
{
	if (setArgs(args))
		return(mergeQueue());
	else
		return (NULL);
}

std::list<int>	*PmergeMe::sortList(char **args)
{
	if (setArgs(args))
		return(mergeList());
	else
		return (NULL);
}

// Sort Void

std::deque<int>	*PmergeMe::sortQueue(void) const
{
	if (!nums)
		return (NULL);
	std::deque<int>	queue;

	for (size_t i=0; i < nums_size; i++)
		queue.push_back(nums[i]);
	return (new std::deque<int>(msortQueue(queue)));
}

std::list<int>	*PmergeMe::sortList(void) const
{
}

// Divide

std::deque<int>	PmergeMe::msortQueue(const t_ique &a) const
{
	if (a.size() == 1)
		return (a);

	std::deque<int>::const_iterator	begin = a.begin();
	std::deque<int>::const_iterator	itr = begin;
	std::deque<int>::const_iterator	end = a.end();

	for (size_t i = 0; i < a.size() / 2; i++)
		itr++;

	std::deque<int>	arrayOne(begin, itr);
	std::deque<int> arrayTwo(itr, end);

	arrayOne = msortQueue(arrayOne);
	arrayTwo = msortQueue(arrayTwo);
	return (mergeQueue(arrayOne, arrayTwo));
}

// Merge

std::deque<int>	PmergeMe::mergeQueue(const std::deque<int> &a,
		const std::deque<int> &b) const
{
	std::deque<int>	c;
	std::deque<int>::const_iterator	itr_a = a.begin();
	std::deque<int>::const_iterator	itr_b = b.begin();

	while (itr_a != a.end() && itr_b != b.end())
	{
		if (*itr_a > *itr_b)
			c.push_back(*(itr_b++));
		else
			c.push_back(*(itr_a++));
	}
	while (itr_a != a.end())
		c.push_back(*(itr_a++));
	while (itr_b != b.end())
		c.push_back(*(itr_b++));
	return (c);
}
