/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:46 by tcakmako          #+#    #+#             */
/*   Updated: 2023/05/28 22:41:53 by tcakmako         ###   ########.fr       */
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
	t_image		img;
	t_objects	*objects;

	img.height = height;
	img.width = width;
	if (check_argc(argc))
		return (1);
	objects = parse(argv[1], ASPECT_RATIO);
	if (!objects)
		return (1);
	printf("P3\n%d %d\n255\n", width, height);
	if (SAMPLES_PER_PIXEL == 1)
		draw_ppm_wo_sampling(&img, objects);
	else
		draw_ppm_w_sampling(&img, objects);
	destroy_objects(objects);
	free(objects);
	return (0);
}
