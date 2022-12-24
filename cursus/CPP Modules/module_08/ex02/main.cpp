#include <iostream>
#include <list>
#include "MutantStack.hpp"

template <typename T>
void	compare(MutantStack<T> &mstack, std::list<T> &list)
{
	std::cout << "MutantStack\tList" << std::endl;
	std::cout << "-----------\t-----------" << std::endl;

	mstack.push(5);		list.push_back(5);
	mstack.push(17);	list.push_back(17);
	std::cout << "top :\t" << mstack.top() << "\t";
	std::cout << "top :\t" << list.back() << std::endl;
	mstack.pop();		list.pop_back();
	std::cout << "size :\t" << mstack.size() << "\t";
	std::cout << "size :\t" << list.size() << std::endl;
	std::cout << "-----------\t-----------" << std::endl;
	mstack.push(3);		list.push_back(3);
	mstack.push(5);		list.push_back(5);
	mstack.push(737);	list.push_back(737);
	mstack.push(0);		list.push_back(0);
	typename MutantStack<T>::iterator s_it = mstack.begin();
	typename MutantStack<T>::iterator s_ite = mstack.end();
	typename std::list<T>::iterator l_it = list.begin();
	typename std::list<T>::iterator l_ite = list.end();
	++s_it;		++l_it;
	--s_ite;	--l_ite;
	while (l_it != l_ite)
	{
		std::cout << "\t" << *s_it << "\t\t" << *l_it << std::endl;
		++l_it;
		++s_it;
	}
}

int	main(void)
{
//	MutantStack<int>			x;
//	MutantStack<int>::iterator	itr;
//
//	x.push(10);
//	x.push(4);
//	x.push('h');

	MutantStack<int>	mstack;
	std::list<int>		list;
	compare(mstack, list);
	std::stack<int> s(mstack);

	return (0);
}
