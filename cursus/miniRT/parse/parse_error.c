/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:32:05 by hece              #+#    #+#             */
/*   Updated: 2023/05/26 20:32:06 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

void
	ft_plane_error_check(char **split, t_objects *objects)
{
	register int	index;

	index = 0;
	while (index < 3)
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
	index = -1;
	while (++index < 3)
	{
		if ((ft_check_comma(split[index], ',')) != 2)
		{
			printf("ERROR ! = arguments with missing paramters\n");
			free_split_check_func(split);
			destroy_objects(objects);
			exit(1);
		}
	}
}

void
	ft_light_error_check(char **split, t_objects *objects)
{
	register int	index;

	index = 0;
	while (index < 3)
	{
		if (split[index] == NULL)
		{
			printf("ERROR ! = missing arguments\n");
			free_split_check_func(split);
			destroy_objects(objects);
			exit(1);
		}
		index++;
	}
	if (((ft_check_comma(split[0], ',')) != 2)
		|| ((ft_check_comma(split[2], ',')) != 2))
	{
		printf("ERROR ! = argument with missing paramter\n");
		free_split_check_func(split);
		destroy_objects(objects);
		exit(1);
	}
}

void
	ft_ambient_light_error_check(char **split, t_objects *objects)
{
	register int	index;

	index = 0;
	while (index < 2)
	{
		if (split[index] == NULL)
		{
			printf("ERROR ! = missing argument\n");
			destroy_objects(objects);
			free_split_check_func(split);
			exit(1);
		}
		index++;
	}
	if (ft_check_comma(split[1], ',') != 2)
	{
		printf("ERROR ! = argument with missing parameters\n");
		destroy_objects(objects);
		free_split_check_func(split);
		exit(1);
	}
}

void
	ft_camera_error_check(char **split, t_objects *objects)
{
	register int	index;

	index = 0;
	while (index < 3)
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
		|| ((ft_check_comma(split[1], ',')) != 2))
	{
		printf("ERROR ! = arguments with missing paramters\n");
		destroy_objects(objects);
		free_split_check_func(split);
		exit(1);
	}
}

void
	ft_sphere_error_check(char **split, t_objects *objects)
{
	register int	index;

	index = 0;
	while (index < 3)
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
	if ((ft_check_comma(split[0], ',') != 2)
		|| ((ft_check_comma(split[2], ',')) != 2))
	{
		printf("ERROR ! = arguments with missing parameters\n");
		destroy_objects(objects);
		free_split_check_func(split);
		exit(1);
	}
}
