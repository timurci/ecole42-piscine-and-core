/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_create_objects_two.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:32:19 by hece              #+#    #+#             */
/*   Updated: 2023/05/26 20:32:20 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void
	ft_free_tmp_split(t_split_tmp *tmp)
{
	free_split(tmp->split_tmp0);
	free_split(tmp->split_tmp1);
	free_split(tmp->split_tmp2);
}

t_objects
	*create_sphere(char **split, t_objects *objects)
{
	t_point3	center;
	float		radius;
	t_color3	color;
	char		**split_tmp0;
	char		**split_tmp2;

	ft_sphere_error_check(split, objects);
	split_tmp0 = ft_split(split[0], ',');
	center.x = ft_atof(split_tmp0[0]);
	center.y = ft_atof(split_tmp0[1]);
	center.z = ft_atof(split_tmp0[2]);
	radius = ft_atof(split[1]);
	split_tmp2 = ft_split(split[2], ',');
	color.x = ft_atof(split_tmp2[0]) / 255.999f;
	color.y = ft_atof(split_tmp2[1]) / 255.999f;
	color.z = ft_atof(split_tmp2[2]) / 255.999f;
	objects->sphere = add_sphere(objects->sphere, center, radius, color);
	free_split(split_tmp0);
	free_split(split_tmp2);
	return (objects);
}
