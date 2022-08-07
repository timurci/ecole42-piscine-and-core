/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:50:32 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/03 13:48:17 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_array(t_ints *list, char *name)
{
	size_t	itr;

	itr = 0;
	if (name)
		ft_printf("%s = [", name);
	else
		ft_printf("List = [");
	while (itr < list->inv)
	{
		ft_printf("%d", list->arr[itr]);
		if (itr != list->inv - 1)
			ft_printf(", ");
		itr++;
	}
	ft_printf("]\n");
}
