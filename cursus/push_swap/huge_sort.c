/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huge_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:41:41 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/13 16:44:30 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	try_mutual_rotation(t_ints *a, t_ints *b, int min, int max)
{
	int	b_value;
	int	a_value;

	b_value = b->arr[locate_closest_element(b, min, max, 'b')];
	a_value = find_prev(a, b_value);
	if (a_value == b_value)
		a_value = min_element(a);
	mutual_rotation(a, b, a_value, b_value);
}

static void	mutual_sort(t_ints *a, t_ints *b)
{
	int	former;

	former = find_prev(a, b->arr[b->inv - 1]);
	if (former == b->arr[b->inv - 1])
		former = min_element(a);
	rotate_to_top(a, former, 'a');
	push(a, b, "pa");
}

static void	sort_stack(t_ints *a, t_ints *b)
{
	int	b_min;
	int	b_max;

	while (b->inv > 0)
	{
		b_min = min_element(b);
		b_max = max_element(b);
		try_mutual_rotation(a, b, b_min, b_max);
		mvclosest_to_top(b, b_min, b_max, "bb");
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
	steps_to_sort = a->inv / (((a->inv / 500) + 1) * 50) + 1;
	sorting_size = a->inv / steps_to_sort;
	limits[1] = max_element(a);
	while (steps_to_sort > 0)
	{
		if (is_shift_sorted(a))
			break ;
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
