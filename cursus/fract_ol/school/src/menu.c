/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:37:17 by tcakmako          #+#    #+#             */
/*   Updated: 2022/06/22 12:37:18 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static char	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

static void	print_options(char option)
{
	if (option == 0)
	{
		ft_printf("Insufficient arguments.\n");
		ft_printf("Usage: \"./fractol <option>\"\n");
	}
	else if (option == 1)
		ft_printf("Incorrect argument!\n");
	else if (option == 2)
		ft_printf("Too many arguments.\n");
	ft_printf("Available options:\n");
	ft_printf("\tblank, mandelbrot, julia\n");
	exit(EXIT_FAILURE);
}

void	menu(t_mlx *app, int ac, char **av)
{
	if (ac < 2)
		print_options(0);
	else if (ac > 2)
		print_options(2);
	av++;
	if (!ft_strcmp("blank", *av))
		;
	else if (!ft_strcmp("mandelbrot", *av))
		call_item(app, mandelbrot, 1);
	else if (!ft_strcmp("julia", *av))
		call_item(app, julia, 2);
	else
		print_options(1);
}
