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

# include <stdbool.h>

t_color3	ray_color(const t_ray3 r)
{
	t_vec3	unit_dir = vector3_unit(r.direction);
	float	t = 0.5 * (unit_dir.y * + 1.0);
	return (vector3_add(vector3_scm(color3_set(1.0, 1.0, 1.0), 1.0 - t),
						vector3_scm(color3_set(0.3, 0.5, 1.0), t)
						)
			);
}

void	fill_strange(t_mlx_image *img, t_point3 left_corner, t_vec3 hl, t_vec3 vl)
{
	t_point3	origin = point3_set(0, 0, 0);

	for (int j = img->height - 1; j >= 0; --j)
	{
		printf("\33[2K\rScanlines remaining : %d", j);
		fflush(stdout);
		for (int i = 0; i < img->width; ++i)
		{
			double	u = (double) i / (img->width - 1);
			double	v = (double) (img->height - j) / (img->height - 1);
			//double	b = 0.25;
			t_ray3	r = ray3_set(origin,
								vector3_add(left_corner,
											vector3_add(vector3_scm(hl, u),
														vector3_add(vector3_scm(vl, v),
																	vector3_scm(origin, -1))
														)
											)
								);

			int	color = color3_get_color(ray_color(r));
			
			//t_mlx_image_set_pixel(img, i, j, rgb_to_color(r * 255.999,g * 255.999,b * 255.999));
			t_mlx_image_set_pixel(img, i, j, color);
		}
	}
	printf("\nDone.\n");
}

void	fill_bg(t_mlx_image *img, int color)
{
	for (int i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->width; j++)
		{
			t_mlx_image_set_pixel(img, j, i, color);
		}
	}
}

int	main(void)
{
	const float	aspect_ratio = 16.0 / 9.0;
	const int	width = 1080;
	const int	height = width / aspect_ratio;

	const float	viewport_h = 1.5;
	const float viewport_w = aspect_ratio * viewport_h;
	const float focal_length = 1.0;

	const t_point3	origin = point3_set(0, 0, 0);
	const t_vec3	horizontal = vector3_set(viewport_w, 0, 0);
	const t_vec3	vertical = vector3_set(0, viewport_h, 0);
	const t_point3	lower_left_corner = vector3_add(origin,
													vector3_add(vector3_scm(horizontal , -0.5),
																vector3_add(vector3_scm(vertical, 0.5),
																			vector3_set(0, 0, -focal_length))
																)
													);


	t_mlx_core	*mlx_core;

	mlx_core = t_mlx_init_core(width, height, "Test Application");
	mlx_loop_hook(mlx_core->ptr, t_mlx_loop_hook, mlx_core);
	mlx_key_hook(mlx_core->win, t_mlx_key_hook, mlx_core);
	mlx_hook(mlx_core->win, 17, 0, terminate, mlx_core);

	//test
	fill_bg(mlx_core->frame[0], 0x00FF0000);
	//fill_bg(mlx_core->frame[1], 0x0000FF00);
	fill_strange(mlx_core->frame[1], lower_left_corner, horizontal, vertical);
	//test
	
	mlx_loop(mlx_core->ptr);
	t_mlx_destroy_core(mlx_core);
	return (0);
}
