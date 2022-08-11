/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:43:12 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/03 17:07:44 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_prev(t_ints *list, int n)
{
	size_t	itr;
	int		tmp;

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

int	find_next(t_ints *list, int n)
{
	size_t	itr;
	int		tmp;

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
