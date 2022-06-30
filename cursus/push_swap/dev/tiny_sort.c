#include "push_swap.h"

static void	tri_sort(t_ints *a)
{
	int	*l;

	l = a->arr;

	if (l[0] > l[1] && l[1] < l[2] && l[2] < l[0])
		swap(a, "sa");
	else if (l[0] > l[1] && l[1] < l[2] && l[2] > l[0])
		rot(a, "ra");
	else if (l[0] < l[1] && l[1] > l[2] && l[2] > l[0])
		rrot(a, "rra");
	else if (l[0] < l[1] && l[1] < l[2] && l[2] > l[0])
	{
		swap(a, "sa");
		rrot(a, "rra");
	}
	else if (l[0] < l[1] && l[1] > l[2] && l[2] < l[0])
	{
		swap(a, "sa");
		rot(a, "ra");
	}
}

static void	double_tiny_sort(t_ints *a, t_ints *b)
{
}

void	tiny_sort(t_ints *a)
{
	t_ints	*b;

	if (a->inv > 3)
	{
		b = dup_ints(a);
		push(a, b, "pb");
		push(a, b, "pb");
		double_tiny_sort(a, b);
	}
	else
		tri_sort(a);
}
