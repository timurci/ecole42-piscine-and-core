#include "push_swap.h"

int	max_element(t_ints *list)
{
	size_t	itr;
	int		tmp;

	itr = 0;
	tmp = -2147483648;
	while (itr < list->inv)
	{
		if (tmp < list->arr[itr])
			tmp = list->arr[itr];
		itr++;
	}
	return (tmp);
}

int	min_element(t_ints *list)
{
	size_t	itr;
	int		tmp;

	itr = 0;
	tmp = 2147483647;
	while (itr < list->inv)
	{
		if (tmp > list->arr[itr])
			tmp = list->arr[itr];
		itr++;
	}
	return (tmp);
}

void	rotate_to_top(t_ints *l, int n, char stack_name)
{
	int	index;

	index = 0;
	while (l->arr[index] != n && index < l->inv)
		index++;
	if (index == l->inv)
		return ;
	while (n != l->arr[l->inv - 1])
	{
		if (index < l->inv / 2 && stack_name == 'b')
			rrot(l, "rrb");
		else if (index < l->inv / 2 && stack_name == 'a')
			rrot(l, "rra");
		else if (stack_name == 'b')
			rot(l, "rb");
		else
			rot(l, "ra");
	}
}
