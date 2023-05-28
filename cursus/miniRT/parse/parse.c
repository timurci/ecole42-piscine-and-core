/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:32:00 by hece              #+#    #+#             */
/*   Updated: 2023/05/26 20:32:00 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

t_objects
	*create_objects(char **split, t_objects *objects, const float aspect_ratio)
{
	if (ft_strncmp(split[0], "C", 1) == 0)
		objects = create_camera(split + 1, objects, aspect_ratio);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		objects = create_sphere(split + 1, objects);
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		objects = create_cylinder(split + 1, objects);
	else if (ft_strncmp(split[0], "pl", 2) == 0)
		objects = create_plane(split + 1, objects);
	else if (ft_strncmp(split[0], "L", 1) == 0)
		objects = create_light(split + 1, objects);
	else if (ft_strncmp(split[0], "A", 1) == 0)
		objects = create_ambient_light(split + 1, objects);
	return (objects);
}

void
	object_init(t_objects *objects)
{
	objects->sphere = NULL;
	objects->plane = NULL;
	objects->cylinder = NULL;
}

t_objects
	*parse_objects(int fd, const float aspect_ratio)
{
	t_objects		*objects;
	char			*line;
	char			**split;
	int				index;
	t_compulsory	test;

	index = -1;
	objects = (t_objects *)malloc(sizeof(*objects));
	object_init(objects);
	line = get_next_line(fd);
	while (line != NULL)
	{
		split = ft_split(line, ' ');
		ft_compulsory(&test, split);
		objects = create_objects(split, objects, aspect_ratio);
		free(line);
		while (++index && split[index] != NULL)
			free(split[index]);
		index = -1;
		free(split);
		line = get_next_line(fd);
	}
	free(line);
	ft_compulsory_check(&test, objects);
	return (objects);
}

t_objects
	*parse(const char *filename, const float aspect_ratio)
{
	int			fd;
	t_objects	*objects;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("the file dont opened\n");
		return (NULL);
	}
	objects = parse_objects(fd, aspect_ratio);
	if (close(fd) == -1)
		return (NULL);
	return (objects);
}
