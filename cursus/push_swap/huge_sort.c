/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huge_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:41:41 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/03 12:49:14 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	mutual_sort(t_ints *a, t_ints *b)
{
	int	former;

	former = locate_prev(a, b->arr[b->inv - 1]);
	if (former == b->arr[b->inv - 1])
		former = min_element(a);
	rotate_to_top(a, former, 'a');
	push(a, b, "pa");
}

static void	sort_stack(t_ints *a, t_ints *b)
{
	while (b->inv > 0)
	{
		mvclosest_to_top(b, min_element(b), max_element(b), "bb");
		mutual_sort(a, b);
	}
}

static void	move_to_b(t_ints *a, t_ints *b, int *range, int itr)
{
	while (itr--)
	{
		mvclosest_to_top(a, range[0], range[1], "ra");
		push(a, b, "pb");
	}
}

void	huge_sort(t_ints *a)
{
	t_ints	*b;
	int		limits[2];
	size_t	steps_to_sort;
	size_t	sorting_size;

	b = dup_ints(a);
	steps_to_sort = a->inv / STEP_CONSTANT + 1;
	sorting_size = a->inv / steps_to_sort;
	limits[1] = max_element(a);
	while (steps_to_sort > 0)
	{
		if (steps_to_sort == 1 || (long) sorting_size >= (long) limits[1])
			limits[0] = min_element(a);
		else
			limits[0] = limits[1] - sorting_size + 1;
		move_to_b(a, b, limits, sorting_size);
		sort_stack(a, b);
		limits[1] = limits[0] - 1;
		steps_to_sort--;
	}
	rotate_to_top(a, min_element(a), 'a');
	delete_ints(b);
}
