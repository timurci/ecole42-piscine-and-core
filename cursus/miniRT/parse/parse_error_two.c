/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:33:06 by hece              #+#    #+#             */
/*   Updated: 2023/05/26 20:33:08 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

void
	ft_cylinder_check_error(char **split, t_objects *objects)
{
	register int	index;

	index = 0;
	while (index < 5)
	{
		if (split[index] == NULL)
		{
			printf("ERROR ! = missing arguments\n");
			destroy_objects(objects);
			free_split_check_func(split);
			exit(1);
		}
		index++;
	}
	if (((ft_check_comma(split[0], ',')) != 2)
		|| ((ft_check_comma(split[1], ',')) != 2)
		|| ((ft_check_comma(split[4], ',')) != 2))
	{
		printf("ERROR ! = arguments with missing paramters\n");
		destroy_objects(objects);
		free_split_check_func(split);
		exit(1);
	}
}

void
	ft_compulsory(t_compulsory *test, char **split)
{
	if (ft_strncmp(split[0], "L", 1) == 0)
		test->l = true;
	else if (ft_strncmp(split[0], "A", 1))
		test->a = true;
	else if (ft_strncmp(split[0], "C", 1))
		test->c = true;
}

void
	ft_compulsory_check(t_compulsory *test, t_objects *objects)
{
	if (test->a != true || test->c != true || test->l != true)
	{
		printf("mandatory parameters are missing\n");
		destroy_objects(objects);
		exit(1);
	}
}
