#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>
# include <iterator>

template <typename T>
class	MutantStack : public std::stack<T>
{
	public:
		class	iterator;
	
	public:
		MutantStack<T>(void);
		MutantStack<T>(const MutantStack &);
		~MutantStack<T>(void);

		MutantStack<T>	&operator=(const MutantStack<T> &);
		iterator		begin(void);
		iterator		end(void);
};

template <typename T>
class	MutantStack<T>::iterator :
	public std::iterator<std::bidirectional_iterator_tag, T>
{
	private:
		T	*p;

	public:
		iterator(void);
		iterator(const iterator &);
		iterator(T *);
		~iterator(void);

		iterator	&operator=(const iterator &);
		iterator	&operator=(T *);
		iterator	&operator++(void);
		iterator	operator++(int);
		iterator	&operator--(void);
		iterator	operator--(int);
		T			&operator*(void);
		bool		operator==(const iterator &);
		bool		operator!=(const iterator &);
};

# include "MutantStack.tpp"

#endif
