/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutual_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:24:15 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/13 16:24:16 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	rot_type(t_ints *l, int n)
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
}
