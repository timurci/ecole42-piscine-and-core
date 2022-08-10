/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:50:57 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/10 17:37:41 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_ints	*a;

	if (ac == 1)
		return (0);
	a = parse_args(ac, av);
	//print_array(a, "a bgn");
	a = form_index(a);
	//print_array(a, "a ind");
	while (!is_sorted(a))
	{
		if (a->inv <= 5)
			tiny_sort(a);
		else
			huge_sort(a);
	}
	//print_array(a,0);
	return (0);
}
