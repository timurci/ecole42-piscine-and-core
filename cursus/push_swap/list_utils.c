/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:42:40 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/03 12:49:36 by tcakmako         ###   ########.fr       */
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

/*char	rot_type(t_ints *l, int n)
{
	size_t	index;

	index = 0;
	while (l->arr[index] != n && index < l->inv)
		index++;
	if (index == l->inv)
		return (-1);
	else if (index < l->inv / 2)
		return (1);
	else
		return (0);
}

void	mutual_rotation(t_ints *l1, t_ints *l2, int n1, int n2)
{
	char	type[2];

	type[0] = rot_type(l1, n1);
	type[1] = rot_type(l2, n2);
	if (type[0] == type[1])
	{
		if (type[0] == 0)
		{
			while (l1->arr[l1->inv - 1] != n1
					&& l2->arr[l2->inv - 1] != n2)
			{
				rot(l1, "rr");
				rot(l2, "0r");
			}
		}
		else if (type[0] == 1)
		{
			while (l1->arr[l1->inv - 1] != n1
					&& l2->arr[l2->inv - 1] != n2)
			{
				rrot(l1, "rrr");
				rrot(l2, "0rr");
			}
		}
	}
}*/

void	mvclosest_to_top(t_ints *l, int min, int max, char *mode)
{
	int	index;

	index = locate_closest_element(l, min, max, mode[0]);
	rotate_to_top(l, l->arr[index], mode[1]);
}
