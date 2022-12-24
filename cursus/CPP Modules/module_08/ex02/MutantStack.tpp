template <typename T>
MutantStack<T>::MutantStack(void)
{}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &other)
{}

template <typename T>
MutantStack<T>::~MutantStack(void)
{}

template <typename T>
MutantStack<T>	&MutantStack<T>::operator=(const MutantStack<T> &other)
{}

template <typename T>
typename MutantStack<T>::iterator	MutantStack<T>::begin(void)
{return (&this->c.front());}

template <typename T>
typename MutantStack<T>::iterator	MutantStack<T>::end(void)
{return (&this->c.back() + 1);}

/******************************************************************
************************Iterator definitions***********************
******************************************************************/

template <typename T>
MutantStack<T>::iterator::iterator(void) : p(NULL)
{}

template <typename T>
MutantStack<T>::iterator::iterator(const iterator &other) : p(other.p)
{}

template <typename T>
MutantStack<T>::iterator::iterator(T *np) : p(np)
{}

template <typename T>
MutantStack<T>::iterator::~iterator(void)
{}

template <typename T>
typename MutantStack<T>::iterator
	&MutantStack<T>::iterator::operator=(const iterator &other)
{p = other.p;}

template <typename T>
typename MutantStack<T>::iterator
	&MutantStack<T>::iterator::operator=(T *np)
{p = np;}

template <typename T>
typename MutantStack<T>::iterator
	&MutantStack<T>::iterator::operator++(void)
{++p; return (*this);}

template <typename T>
typename MutantStack<T>::iterator
	MutantStack<T>::iterator::operator++(int)
{iterator	tmp(*this); operator++(); return (tmp);}

template <typename T>
typename MutantStack<T>::iterator
	&MutantStack<T>::iterator::operator--(void)
{--p; return (*this);}

template <typename T>
typename MutantStack<T>::iterator
	MutantStack<T>::iterator::operator--(int)
{iterator	tmp(*this); operator--(); return (tmp);}

template <typename T>
T
	&MutantStack<T>::iterator::operator*(void)
{return (*p);}

template <typename T>
bool
	MutantStack<T>::iterator::operator==(const iterator &other)
{return (p == other.p);}

template <typename T>
bool
	MutantStack<T>::iterator::operator!=(const iterator &other)
{return (p != other.p);}
