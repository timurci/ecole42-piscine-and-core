/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huge_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:41:41 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/07 18:03:45 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	init_bound(t_ints *l)
{
	int		max;
	char	scan;
	char	itr;

	itr = 0;
	scan = 0;
	max = max_element(l);
	while (scan < 32)
	{
		if ((max >> scan) & 1)
			itr = scan;
		scan++;
	}
	return (itr + 1);
}

static void	move_to_b(t_ints *a, t_ints *b, char itr)
{
	size_t	scan;

	scan = 0;
	while (scan < a->inv)
	{
		if (!((a->arr[scan] >> itr) & 1))
		{
			rot_until_top(a, a->arr[scan], 'a');
			//rotate_to_top(a, a->arr[scan], 'a');
			push(a, b, "pb");
		}
		scan++;
	}
}

static void	reorder_a(t_ints *a, char itr)
{
	if (itr == 0)
		return ;
	while (a
}

void	huge_sort(t_ints *a)
{
	t_ints	*b;
	char	itr;
	char	upper_bound;

	b = dup_ints(a);
	upper_bound = init_bound(a);
	itr = 0;
	while (itr < upper_bound)
	{
		move_to_b(a, b, itr);
		while (b->inv)
		{
			//rotate_to_top(b, max_element(b), 'b');
			push(a, b, "pa");
		}
		//if (is_shift_sorted(a))
		//	break ;
	}
	rotate_to_top(a, min_element(a), 'a');
	delete_ints(b);
}
