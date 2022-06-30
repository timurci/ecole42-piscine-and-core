#include "push_swap.h"

int locate_prev(t_ints *list, int n)
{
	int	itr;
	int	tmp;

	tmp = max_element(list);
	if (list->inv == 0 || n > tmp)
		return (n);
	itr = 0;
	while (itr < list->inv)
	{
		if (list->arr[itr] > n && list->arr[itr] < tmp)
			tmp = list->arr[itr];
		itr++;
	}
	return (tmp);
}

int locate_next(t_ints *list, int n)
{
	int	itr;
	int	tmp;

	tmp = min_element(list);
	if (list->inv == 0 || n < tmp)
		return (n);
	itr = 0;
	while (itr < list->inv)
	{
		if (list->arr[itr] < n && list->arr[itr] > tmp)
			tmp = list->arr[itr];
		itr++;
	}
	return (tmp);
}
