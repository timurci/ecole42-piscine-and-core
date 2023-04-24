/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:46 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/24 10:51:40 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include "ray3.h"
#include "color3.h"
#include "vector3_utils.h"
#include "vector3_utils_extended.h"

#include <stdbool.h>
#include <math.h>

#include "objects.h"
#include "object_parameters.h"
#include "object_sphere.h"
#include "object_camera.h"
#include "object_light.h"

#include "draw_ppm.h"

#ifndef WIDTH
# define WIDTH 800
#endif

#ifndef ASPECT_RATIO
# define ASPECT_RATIO 1.77777777f
#endif

static void add_objects(t_objects *objects, const float aspect_ratio)
{
	objects->camera = camera_set(aspect_ratio, 66, vector3_set(0, 0, -1), point3_set(0, 0, 5));

	objects->sphere = add_sphere(objects->sphere, point3_set(0, 0, -1), 0.5, color3_set(0,1,0));
	objects->sphere = add_sphere(objects->sphere, point3_set(0, -100.5, -1), 100, color3_set(0.8, 0.8, 0.0));
	objects->sphere = add_sphere(objects->sphere, point3_set(-1, 1, -2), 0.5, color3_set(0.7, 0.3, 0.3));
	//objects->sphere = add_sphere(objects->sphere, point3_set(1, -0.6, -2), 0.5, color3_set(0.5, 0.5, 0.5));
	//objects->sphere = add_sphere(objects->sphere, point3_set(4, 5, -5), 1, color3_set(0.5, 0.5, 0.5));

	//objects->plane = add_plane(objects->plane, point3_set(1,0,-10), vector3_set(1, 0, 0.7), color3_set(0.1, 0.1, 1));
	//objects->plane = add_plane(objects->plane, point3_set(-1,0,-10), vector3_set(-1, 0, 0.7), color3_set(1, 0.1, 0.1));
	
	objects->cylinder = add_cylinder(objects->cylinder, point3_set(-1, 2, -5),
							cylinder_params(1, 2, vector3_set(0.7, 0.2, 1)), color3_set(1, 0, 1));
	objects->cylinder = add_cylinder(objects->cylinder, point3_set(2, 1, -5),
							cylinder_params(1, 5, vector3_set(-0.7, 0.2, 1)), color3_set(1, 0.2, 0));
	objects->cylinder = add_cylinder(objects->cylinder, point3_set(2, 2, -5),
							cylinder_params(1, 5, vector3_set(-0.7, 0.2, -1)), color3_set(0, 0.5, 1));

	objects->point_light = set_point_light(color3_set(1, 1, 1), 1.0f, point3_set(-4, 3, 1));
	objects->ambient_light = set_ambient_light(color3_set(0.3, 0.5, 1.0), 0.5f);
}

int	main(void)
{
	const float	aspect_ratio = ASPECT_RATIO;
	const int	width = WIDTH;
	const int	height = width / aspect_ratio;
	t_image		img;

	img.height = height;
	img.width = width;
	t_objects	*objects = malloc(sizeof(*objects));

	objects->sphere = NULL;
	objects->plane = NULL;
	objects->cylinder = NULL;
	
	add_objects(objects, aspect_ratio);

	printf("P3\n%d %d\n255\n", width, height);

	if (SAMPLES_PER_PIXEL == 1)
		draw_ppm_wo_sampling(&img, objects);
	else
		draw_ppm_w_sampling(&img, objects);
	
	destroy_objects(objects);
	free(objects);
	
	return (0);
}
