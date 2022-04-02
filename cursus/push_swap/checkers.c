#include "push_swap.h"

static char	is_alloc(void *p1, void *p2)
{
	if (!p1 || !p2)
	{
		if (p1)
			free(p1);
		if (p2)
			free(p2);
		return (0);
	}
	return (1);
}

static char	is_repeated(t_ints *ints, int element, int index)
{
	int	scan;

	scan = 0;
	while (scan < index)
	{
		if (element == ints->list[scan])
			return (1);
		scan++;
	}
	return (0);
}

t_ints	*convert_args(int ac, char **av)
{
	t_ints	*ints;
	int		*ilist;
	int		scan;

	ints = malloc(sizeof(t_ints));
	ilist = malloc(sizeof(int) * (ac - 1));
	if (!is_alloc(ints, ilist))
		return (NULL);
	ints->list = ilist;
	ints->list_size = ac - 1;
	av++;
	scan = 0;
	while (scan < ac - 1)
	{
		ilist[scan] = fatoi(av[scan]);
		if ((ilist[scan] == 0 && (*av[scan] != '0' || strlen(av[scan]) != 1))
			|| is_repeated(ints, ilist[scan], scan))
		{
			free(ilist);
			free(ints);
			return (NULL);
		}
		scan++;
	}
	return (ints);
}

static void	sort_list(t_ints *ints)
{
	int	pivot;
	int	scan;
	int	pivot_index;

	pivot_index = 0;
	while (pivot_index < ints->list_size)
	{
		pivot = ints->list[pivot_index];
		scan = pivot_index + 1;
		while (scan < ints->list_size)
		{
			if (pivot > ints->list[scan])
			{
				ints->list[pivot_index] = ints->list[scan];
				ints->list[scan] = pivot;
				pivot = ints->list[pivot_index];
			}
			scan++;
		}
		pivot_index++;
	}
}

t_ints	*create_sorted(t_ints *ints)
{
	t_ints	*sorted_ints;
	int		*ilist;
	int		scan;

	sorted_ints = malloc(sizeof(t_ints));
	ilist = malloc(sizeof(int) * ints->list_size);
	if (!is_alloc(sorted_ints, ilist))
		return (NULL);
	sorted_ints->list = ilist;
	sorted_ints->list_size = ints->list_size;
	scan = 0;
	while (scan < sorted_ints->list_size)
	{
		ilist[scan] = ints->list[scan];
		scan++;
	}
	sort_list(sorted_ints);
	return (sorted_ints);
}
