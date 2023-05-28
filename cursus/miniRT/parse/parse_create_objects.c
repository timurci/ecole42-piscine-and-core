/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_create_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:32:38 by hece              #+#    #+#             */
/*   Updated: 2023/05/26 20:32:46 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_objects
	*create_camera(char **split, t_objects *objects, const float aspect_ratio)
{
	t_vec3	position;
	t_vec3	direction;
	float	fov;
	char	**split_tmp0;
	char	**split_tmp1;

	ft_camera_error_check(split, objects);
	split_tmp0 = ft_split(split[0], ',');
	split_tmp1 = ft_split(split[1], ',');
	fov = ft_atof(split[2]);
	position.x = ft_atof(split_tmp0[0]);
	position.y = ft_atof(split_tmp0[1]);
	position.z = ft_atof(split_tmp0[2]);
	direction.x = ft_atof(split_tmp1[0]);
	direction.y = ft_atof(split_tmp1[1]);
	direction.z = ft_atof(split_tmp1[2]);
	objects->camera = camera_set(aspect_ratio, fov, direction, position);
	free_split(split_tmp0);
	free_split(split_tmp1);
	return (objects);
}

t_objects
	*create_ambient_light(char **split, t_objects *objects)
{
	float		intensity;
	t_color3	color;
	char		**split_tmp;

	ft_ambient_light_error_check(split, objects);
	intensity = ft_atof(split[0]);
	split_tmp = ft_split(split[1], ',');
	color.x = ft_atof(split_tmp[0]) / 255.999f;
	color.y = ft_atof(split_tmp[1]) / 255.999f;
	color.z = ft_atof(split_tmp[2]) / 255.999f;
	objects->ambient_light = set_ambient_light(color, intensity);
	free_split(split_tmp);
	return (objects);
}

t_objects
	*create_light(char **split, t_objects *objects)
{
	t_point3	position;
	float		intensity;
	t_color3	color;
	char		**split_tmp0;
	char		**split_tmp2;

	ft_light_error_check(split, objects);
	split_tmp0 = ft_split(split[0], ',');
	position.x = ft_atof(split_tmp0[0]);
	position.y = ft_atof(split_tmp0[1]);
	position.z = ft_atof(split_tmp0[2]);
	intensity = ft_atof(split[1]);
	split_tmp2 = ft_split(split[2], ',');
	color.x = ft_atof(split_tmp2[0]) / 255.999f;
	color.y = ft_atof(split_tmp2[1]) / 255.999f;
	color.z = ft_atof(split_tmp2[2]) / 255.999f;
	objects->point_light = set_point_light(color, intensity, position);
	free_split(split_tmp0);
	free_split(split_tmp2);
	return (objects);
}

t_objects
	*create_plane(char **split, t_objects *objects)
{
	t_point3	position;
	t_vec3		normal;
	t_color3	color;
	t_split_tmp	tmp;

	ft_plane_error_check(split, objects);
	tmp.split_tmp0 = ft_split(split[0], ',');
	position.x = ft_atof(tmp.split_tmp0[0]);
	position.y = ft_atof(tmp.split_tmp0[1]);
	position.z = ft_atof(tmp.split_tmp0[2]);
	tmp.split_tmp1 = ft_split(split[1], ',');
	normal.x = ft_atof(tmp.split_tmp1[0]);
	normal.y = ft_atof(tmp.split_tmp1[1]);
	normal.z = ft_atof(tmp.split_tmp1[2]);
	tmp.split_tmp2 = ft_split(split[2], ',');
	color.x = ft_atof(tmp.split_tmp2[0]) / 255.999f;
	color.y = ft_atof(tmp.split_tmp2[1]) / 255.999f;
	color.z = ft_atof(tmp.split_tmp2[2]) / 255.999f;
	objects->plane = add_plane(objects->plane, position, normal, color);
	free_split(tmp.split_tmp0);
	free_split(tmp.split_tmp1);
	free_split(tmp.split_tmp2);
	return (objects);
}

t_objects
	*create_cylinder(char **split, t_objects *objects)
{
	t_point3			position;
	t_cylinder_params	params;
	t_color3			color;
	t_split_tmp			tmp;

	ft_cylinder_check_error(split, objects);
	tmp.split_tmp0 = ft_split(split[0], ',');
	position.x = ft_atof(tmp.split_tmp0[0]);
	position.y = ft_atof(tmp.split_tmp0[1]);
	position.z = ft_atof(tmp.split_tmp0[2]);
	tmp.split_tmp1 = ft_split(split[1], ',');
	params.axis.x = ft_atof(tmp.split_tmp1[0]);
	params.axis.y = ft_atof(tmp.split_tmp1[1]);
	params.axis.z = ft_atof(tmp.split_tmp1[2]);
	params.radius = ft_atof(split[2]) / 2.0f;
	params.height = ft_atof(split[3]);
	tmp.split_tmp2 = ft_split(split[4], ',');
	color.x = ft_atof(tmp.split_tmp2[0]) / 255.999f;
	color.y = ft_atof(tmp.split_tmp2[1]) / 255.999f;
	color.z = ft_atof(tmp.split_tmp2[2]) / 255.999f;
	objects->cylinder = add_cylinder(objects->cylinder,
			position, params, color);
	ft_free_tmp_split(&tmp);
	return (objects);
}
