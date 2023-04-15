/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ppm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 17:15:45 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_PPM_H
# define DRAW_PPM_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include "mlx_utils.h" //needed to access color_to_rgb functions

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

# include "random42.h"

# ifndef SAMPLES_PER_PIXEL
#  define SAMPLES_PER_PIXEL 100
# endif

//# define INV_SAMPLES_PER_PIXEL ((float) 1.0f / SAMPLES_PER_PIXEL) //norm error

# ifndef MAX_DEPTH
#  define MAX_DEPTH 50
# endif

typedef struct s_image
{
	int	width;
	int	height;
}	t_image;

void	draw_ppm_wo_sampling(t_image *img, const t_objects *objs);
void	draw_ppm_w_sampling(t_image *img, const t_objects *objs);

#endif
