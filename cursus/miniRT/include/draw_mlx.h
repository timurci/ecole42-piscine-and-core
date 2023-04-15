#ifndef DRAW_H
# define DRAW_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include "mlx_core.h"
# include "mlx_utils.h"

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

# ifndef SAMPLES_PER_PIXEL
#  define SAMPLES_PER_PIXEL 100
# endif

# define INV_SAMPLES_PER_PIXEL (float) 1.0f / SAMPLES_PER_PIXEL

# ifndef MAX_DEPTH
#  define MAX_DEPTH 50
# endif

void	draw_mlx_wo_sampling(t_mlx_image *img, const t_objects *objs);
void	draw_mlx_w_sampling(t_mlx_image *img, const t_objects *objs);

//void	draw_ppm_wo_sampling(t_mlx_image *img, const t_objects *objs);
//void	draw_ppm_w_sampling(t_mlx_image *img, const t_objects *objs);

#endif
