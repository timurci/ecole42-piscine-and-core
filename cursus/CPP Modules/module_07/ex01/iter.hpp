#ifndef ITER_HPP
# define ITER_HPP

template <class A, class B>
void	iter(A *a, B b, void (*f)(A&))
{
	for (B i = 0; i < b; i++)
		f(a[i]);
}

#endif
