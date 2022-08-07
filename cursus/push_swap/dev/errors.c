/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:49:01 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/03 15:06:49 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	parsing_errors(char mode, void *param)
{
	write(2, "Error\n", 6);
	if (mode == 0)
		ft_printf("Incorrect number of arguments.\n");
	else if (mode == 1)
		ft_printf("Invalid argument at %u.\n", *((unsigned int *) param) + 1);
	else if (mode == 2)
		ft_printf("Repeated argument at %u.\n", *((unsigned int *) param));
	else if (mode == 3)
		ft_printf("INT out of range at %u.\n", *((unsigned int *) param) + 1);
	exit(EXIT_FAILURE);
}
