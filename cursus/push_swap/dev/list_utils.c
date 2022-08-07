/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:42:40 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/07 17:59:03 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	rot_until_top(t_ints *l, int n, char stack_name)
{
	size_t	index;

	index = 0;
	while (l->arr[index] != n && index < l->inv)
		index++;
	if (index == l->inv)
		return ;
	while (n != l->arr[l->inv - 1])
	{
		if (stack_name == 'b')
			rot(l, "rrb");
		else
			rot(l, "rra");
	}
}

void	rotate_to_top(t_ints *l, int n, char stack_name)
{
	size_t	index;

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

void	mvclosest_to_top(t_ints *l, int min, int max, char *mode)
{
	int	index;

	index = locate_closest_element(l, min, max, mode[0]);
	rotate_to_top(l, l->arr[index], mode[1]);
}
