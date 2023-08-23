#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include<deque>
# include<list>
# include<iostream>
# include<cstdlib>
# include<cstring>

class PmergeMe
{
	private:
		char	**args;
		int		*nums;
		size_t	nums_size;

	private:
		typedef std::deque<int> t_ique;
	//	typedef std::list<int> t_ilist;

	private:
		bool	checkArgs(const int *src, const size_t src_size) const;
		t_ique	msortQueue(const t_ique &a) const;
	//	t_ilist	msortList(const t_ilist &a) const;
		t_ique	mergeQueue(const t_ique &a, const t_ique &b) const;
	//	t_ilist	mergeList(const t_ilist &a, const t_ilist &b) const;

	public:
		PmergeMe(void);
		PmergeMe(char **args);
		PmergeMe(const PmergeMe &);
		~PmergeMe(void);

		PmergeMe	&operator=(const PmergeMe &);

	public:
		bool	setArgs(char **args);

		std::deque<int>	*sortQueue(void) const;
		std::deque<int>	*sortQueue(char **args);
	//	void	sortList(void) const;
	//	void	sortList(const char **args);

};

#endif
