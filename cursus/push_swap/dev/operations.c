#include "push_swap.h"

void	push(t_ints *a, t_ints *b, char *mode)
{
	t_ints	*tmp;

	if (mode[1] == 'a')
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	b->arr[b->inv] = a->arr[a->inv - 1];
	b->inv++;
	a->inv--;
	if (*mode == 'p')
		printf("%s\n", mode);
}

void	swap(t_ints *l, char *mode)
{
	int	tmp;

	tmp = l->arr[l->inv - 1];
	l->arr[l->inv - 1] = l->arr[l->inv - 2];
	l->arr[l->inv - 2] = tmp;
	if (*mode == 's')
		printf("%s\n", mode);
}

void	rot(t_ints *l, char *mode)
{
	int		hold[2];
	size_t	scan;

	scan = 0;
	hold[0] = l->arr[0];
	while (scan < l->inv - 1)
	{
		hold[1] = l->arr[scan + 1];
		l->arr[scan + 1] = hold[0];
		hold[0] = hold[1];
		scan++;
	}
	l->arr[0] = hold[0];
	if (*mode == 'r')
		printf("%s\n", mode);
}

void	rrot(t_ints *l, char *mode)
{
	int		hold[2];
	size_t	scan;

	scan = l->inv - 1;
	hold[0] = l->arr[scan];
	while (scan > 0)
	{
		hold[1] = l->arr[scan - 1];
		l->arr[scan - 1] = hold[0];
		hold[0] = hold[1];
		scan--;
	}
	l->arr[l->inv - 1] = hold[0];
	if (*mode == 'r')
		printf("%s\n", mode);
}
