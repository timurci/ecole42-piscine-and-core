/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:32:05 by hece              #+#    #+#             */
/*   Updated: 2023/05/29 13:14:06 by tcakmako         ###   ########.fr       */
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
			printf("Error\nMissing arguments for plane.\n");
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
			printf("Error\nInvalid parameters for plane.\n");
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
			printf("Error\nMissing arguments for point light.\n");
			free_split_check_func(split);
			destroy_objects(objects);
			exit(1);
		}
		index++;
	}
	if (((ft_check_comma(split[0], ',')) != 2)
		|| ((ft_check_comma(split[2], ',')) != 2))
	{
		printf("Error\nInvalid parameters for point light.\n");
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
			printf("Error\nMissing arguments ambient light.\n");
			destroy_objects(objects);
			free_split_check_func(split);
			exit(1);
		}
		index++;
	}
	if (ft_check_comma(split[1], ',') != 2)
	{
		printf("Error\nInvalid parameters ambient light.\n");
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
			printf("Error\nMissing arguments for camera.\n");
			destroy_objects(objects);
			free_split_check_func(split);
			exit(1);
		}
		index++;
	}
	if (((ft_check_comma(split[0], ',')) != 2)
		|| ((ft_check_comma(split[1], ',')) != 2))
	{
		printf("Error\nInvalid parameters for camera.\n");
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
			printf("Error\nMissing arguments for sphere.\n");
			destroy_objects(objects);
			free_split_check_func(split);
			exit(1);
		}
		index++;
	}
	if ((ft_check_comma(split[0], ',') != 2)
		|| ((ft_check_comma(split[2], ',')) != 2))
	{
		printf("Error\nInvalid parameters for sphere.\n");
		destroy_objects(objects);
		free_split_check_func(split);
		exit(1);
	}
}
