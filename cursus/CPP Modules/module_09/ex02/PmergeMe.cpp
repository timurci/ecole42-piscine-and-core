#include "PmergeMe.hpp"

// Constructors & Destructors & Operators

PmergeMe::PmergeMe(void) : args(NULL), nums(NULL), nums_size(0)
{}


PmergeMe::PmergeMe(char **args) : args(NULL), nums(NULL), nums_size(0)
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
	nums_size = other.nums_size;
	return (*this);
}

// setArgs & checkArgs

bool	PmergeMe::setArgs(char **new_args)
{
	size_t	size = 0;

	while (new_args[size])
	{
		if (!strlen(new_args[size]))
		{
			size = 0;
			break ;
		}
		size++;
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
		if (src[i] < 0)
			return (false);
	}
	return (true);
}

// Sort Args

std::deque<int>	*PmergeMe::sortQueue(char **args)
{
	if (setArgs(args))
		return(sortQueue());
	else
		return (NULL);
}

std::list<int>	*PmergeMe::sortList(char **args)
{
	if (setArgs(args))
		return(sortList());
	else
		return (NULL);
}

// Sort Void

std::deque<int>	*PmergeMe::sortQueue(void) const
{
	if (!nums)
		return (NULL);
	std::deque<int>	queue;

	for (size_t i = 0; i < nums_size; i++)
		queue.push_back(nums[i]);
	return (new std::deque<int>(msortQueue(queue)));
}

std::list<int>	*PmergeMe::sortList(void) const
{
	if (!nums)
		return (NULL);
	std::list<int>	list;

	for (size_t i = 0; i < nums_size; i++)
		list.push_back(nums[i]);
	return (new std::list<int>(msortList(list)));
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

std::list<int>	PmergeMe::msortList(const t_ilist &a) const
{
	if (a.size() == 1)
		return (a);

	std::list<int>::const_iterator	begin = a.begin();
	std::list<int>::const_iterator	itr = begin;
	std::list<int>::const_iterator	end = a.end();

	for (size_t i = 0; i < a.size() / 2; i++)
		itr++;

	std::list<int>	arrayOne(begin, itr);
	std::list<int> arrayTwo(itr, end);

	arrayOne = msortList(arrayOne);
	arrayTwo = msortList(arrayTwo);
	return (mergeList(arrayOne, arrayTwo));
}

// Merge

std::deque<int>	PmergeMe::mergeQueue(const t_ique &a, const t_ique &b) const
{
	bool									flag;
	std::deque<int>							c(a);
	std::deque<int>::const_reverse_iterator	ritr_c;
	std::deque<int>::const_iterator			itr_b = b.begin();

while (itr_b != b.end())
{
	ritr_c = c.rbegin();
	flag = false;
	while (ritr_c != c.rend() && !flag)
	{
		if (*ritr_c < *itr_b)
		{
			c.insert(ritr_c.base(), *itr_b);
			flag = true;
		}
		++ritr_c;
	}
	if (!flag)
		c.push_front(*itr_b);
	++itr_b;
}
	return (c);
}


std::list<int>	PmergeMe::mergeList(const t_ilist &a, const t_ilist &b) const
{
	bool									flag;
	std::list<int>							c(a);
	std::list<int>::const_reverse_iterator	ritr_c;
	std::list<int>::const_iterator			itr_b = b.begin();

while (itr_b != b.end())
{
	ritr_c = c.rbegin();
	flag = false;
	while (ritr_c != c.rend() && !flag)
	{
		if (*ritr_c < *itr_b)
		{
			c.insert(ritr_c.base(), *itr_b);
			flag = true;
		}
		++ritr_c;
	}
	if (!flag)
		c.push_front(*itr_b);
	++itr_b;
}
	return (c);
}

//----------- notes -----------
//queue has classic merge sort, list has insertion sort.
//list has bidirectional iterator while deque does not!
