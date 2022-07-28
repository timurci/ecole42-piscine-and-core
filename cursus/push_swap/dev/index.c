#include "push_swap.h"

static int	closest_from_bottom(t_ints *l, int min, int max, char mode)
{
	int	itr;

	itr = l->inv;
	while (itr-- > 0)
	{
		if (mode == 'r' && l->arr[itr] >= min && l->arr[itr] <= max)
			return (itr);
		else if (mode == 'b' && (l->arr[itr] == min || l->arr[itr] == max))
			return (itr);
	}
	return (-1);
}

static int	closest_from_top(t_ints *l, int min, int max, char mode)
{
	int	itr;

	itr = 0;
	while (itr < l->inv)
	{
		if (mode == 'r' && l->arr[itr] >= min && l->arr[itr] <= max)
			return (itr);
		else if (mode == 'b' && (l->arr[itr] == min || l->arr[itr] == max))
			return (itr);
		itr++;
	}
	return (-1);
}

int	locate_closest_element(t_ints *l, int min, int max, char mode)
{
	int	index[2];

	index[0] = closest_from_top(l, min, max, mode);
	index[1] = closest_from_bottom(l, min, max, mode);
	if (index[0] < l->inv - index[1] - 1)
		return (index[0]);
	else
		return (index[1]);
}
