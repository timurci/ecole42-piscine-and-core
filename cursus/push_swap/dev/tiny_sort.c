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

static void	mutual_sort(t_ints *a, t_ints *b)
{
	int	former;

	former = locate_prev(a, b->arr[b->inv - 1]);
	if (former == b->arr[b->inv - 1])
		former = min_element(a);
	rotate_to_top(a, former, 'a');
	push(a, b, "pa");
}

static void	few_sort(t_ints *a, t_ints *b)
{
	tri_sort(a);
	while (b->inv > 0)
		mutual_sort(a, b);
	rotate_to_top(a, min_element(a), 'a');
}

void	tiny_sort(t_ints *a)
{
	t_ints	*b;

	if (a->inv == 2)
		swap(a, "sa");
	else if (a->inv == 3)
		tri_sort(a);
	else
	{
		b = dup_ints(a);
		push(a, b, "pb");
		if (a->inv > 3)
			push(a, b, "pb");
		few_sort(a, b);
	}
}
