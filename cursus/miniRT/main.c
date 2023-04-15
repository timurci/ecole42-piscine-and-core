/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:46 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 14:19:54 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "mlx_core.h"
#include "mlx_utils.h"
#include "mlx_hook.h"

# include <unistd.h>

# include "ray3.h"
# include "color3.h"
# include "vector3_utils.h"
# include "vector3_utils_extended.h"

# include <stdbool.h>
# include <math.h>

# include "objects.h"
# include "object_parameters.h"
# include "object_sphere.h"
# include "object_camera.h"
# include "object_light.h"

# include "draw_mlx.h"

int	main(void)
{
	const float	aspect_ratio = 16.0f / 9.0f;
	const int	width = 800;
	const int	height = width / aspect_ratio;

	t_mlx_core	*mlx_core;

	mlx_core = t_mlx_init_core(width, height, "miniRT (Test)");
	mlx_loop_hook(mlx_core->ptr, t_mlx_loop_hook, mlx_core);
	mlx_key_hook(mlx_core->win, t_mlx_key_hook, mlx_core);
	mlx_hook(mlx_core->win, 17, 0, terminate, mlx_core);

	t_objects	*objects = malloc(sizeof(*objects));

	objects->sphere = NULL;
	objects->plane = NULL;
	objects->camera = camera_set(aspect_ratio, 66, vector3_set(0, 0, -1), point3_set(0, 0, 5));

	objects->sphere = add_sphere(objects->sphere, point3_set(0, 0, -1), 0.5, color3_set(0,1,0));
	objects->sphere = add_sphere(objects->sphere, point3_set(0, -100.5, -1), 100, color3_set(0.8, 0.8, 0.0));
	objects->sphere = add_sphere(objects->sphere, point3_set(-1, 1, -2), 0.5, color3_set(0.7, 0.3, 0.3));
	//objects->sphere = add_sphere(objects->sphere, point3_set(1, -0.6, -2), 0.5, color3_set(0.5, 0.5, 0.5));
	//objects->sphere = add_sphere(objects->sphere, point3_set(4, 5, -5), 1, color3_set(0.5, 0.5, 0.5));

	//objects->plane = add_plane(objects->plane, point3_set(1,0,-10), vector3_set(1, 0, 0.7), color3_set(0.1, 0.1, 1));
	//objects->plane = add_plane(objects->plane, point3_set(-1,0,-10), vector3_set(-1, 0, 0.7), color3_set(1, 0.1, 0.1));

	objects->point_light = set_point_light(color3_set(1, 1, 1), 1.0f, point3_set(-4, 3, 1));
	objects->ambient_light = set_ambient_light(color3_set(0.3, 0.5, 1.0), 0.5f);
	
	//const float	R = cos(M_PI / 4);
    //
	//objects->sphere = add_sphere(objects->sphere, point3_set(-R, 0, -1), R, color3_set(0, 0, 1));
	//objects->sphere = add_sphere(objects->sphere, point3_set(R, 0, -1), R, color3_set(1, 0, 0));

	printf("P3\n%d %d\n255\n", width, height);

	mlx_core->objects = objects;

	draw_mlx_wo_sampling(mlx_core->frame[0], objects);
	draw_mlx_wo_sampling(mlx_core->frame[1], objects);
	//draw_mlx_w_sampling(mlx_core->frame[1], objects);
	
	t_mlx_core_switch_frame(mlx_core);

	mlx_loop(mlx_core->ptr);
	t_mlx_destroy_core(mlx_core);
	destroy_objects(objects);
	free(objects);
	
	return (0);
}
