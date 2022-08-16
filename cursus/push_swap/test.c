/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:50:57 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/13 16:29:15 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_ints	*a;
	t_ints	*tmp;

	if (ac == 1)
		return (0);
	a = parse_args(ac, av);
	tmp = form_index(a);
	delete_ints(a);
	a = tmp;
	while (!is_sorted(a))
	{
		if (a->inv <= 5)
			tiny_sort(a);
		else
			huge_sort(a);
	}
	return (0);
}
