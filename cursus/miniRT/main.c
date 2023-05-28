/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:46 by tcakmako          #+#    #+#             */
/*   Updated: 2023/05/28 22:40:28 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "mlx_core.h"
#include "mlx_utils.h"
#include "mlx_hook.h"

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

#include "draw_mlx.h"

#include "parse.h"

#ifndef WIDTH
# define WIDTH 800
#endif

#ifndef ASPECT_RATIO
# define ASPECT_RATIO 1.77777777f
#endif

static bool	check_argc(const int argc)
{
	if (argc < 2)
		write(2, "Error: Incomplete number of arguments.\n", 39);
	else if (argc > 2)
		write(2, "Error: Too many arguments.\n", 27);
	else
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	const float	aspect_ratio = ASPECT_RATIO;
	const int	width = WIDTH;
	const int	height = width / aspect_ratio;
	t_objects	*objects;
	t_mlx_core	*mlx_core;

	if (check_argc(argc))
		return (1);
	objects = parse(argv[1], ASPECT_RATIO);
	if (!objects)
		return (1);
	mlx_core = t_mlx_init_core(width, height, "miniRT (Test)");
	mlx_loop_hook(mlx_core->ptr, t_mlx_loop_hook, mlx_core);
	mlx_key_hook(mlx_core->win, t_mlx_key_hook, mlx_core);
	mlx_mouse_hook(mlx_core->win, t_mlx_mouse_hook, mlx_core);
	mlx_hook(mlx_core->win, 17, 0, terminate, mlx_core);
	mlx_core->objects = objects;
	draw_mlx_wo_sampling(mlx_core->frame[0], objects);
	draw_mlx_wo_sampling(mlx_core->frame[1], objects);
	t_mlx_core_switch_frame(mlx_core);
	mlx_loop(mlx_core->ptr);
	t_mlx_destroy_core(mlx_core);
	destroy_objects(objects);
	free(objects);
	return (0);
}
