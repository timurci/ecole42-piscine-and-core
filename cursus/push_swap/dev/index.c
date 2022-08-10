/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:42:18 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/10 12:54:51 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static size_t	closest_from_top(t_ints *l, int min, int max, char mode)
{
	size_t	itr;

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

size_t	locate_closest_element(t_ints *l, int min, int max, char mode)
{
	size_t	index[2];

	index[0] = closest_from_top(l, min, max, mode);
	index[1] = closest_from_bottom(l, min, max, mode);
	if (index[0] < l->inv - index[1] - 1)
		return (index[0]);
	else
		return (index[1]);
}

t_ints	*form_index(t_ints *l)
{
	t_ints	*new_l;
	size_t	scan;
	size_t	steps_left;
	int		target;

	new_l = dup_ints(l);
	new_l->inv = l->inv;
	steps_left = l->inv;
	while (steps_left)
	{
		scan = 0;
		if (steps_left == l->inv)
			target = min_element(l);
		else
			target = locate_prev(l, target);
		while (scan < l->inv)
		{
			if (l->arr[scan] == target)
			{
				new_l->arr[scan] = l->inv - steps_left;
				scan = l->inv - 1;
				steps_left--;
			}
			scan++;
		}
	}
	delete_ints(l);
	return (new_l);
}
