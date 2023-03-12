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
# include <math.h>

# include "objects.h"
# include "object_parameters.h"
# include "object_sphere.h"
# include "object_camera.h"

struct s_helloworld
{
	float	width;
	float	height;
};

t_color3	ray_color(const t_ray3 r, const t_objects objs)
{
	t_hit_record	rec;
	float			t;

	if (hit_objects(r, objs, &rec, set_range(0, INFINITY)))
	{
		return (vector3_scm(vector3_add(rec.n, color3_set(1, 1, 1)), 0.5f));
	}

	t_vec3	unit_dir = vector3_unit(r.direction);
	t = 0.5 * (unit_dir.y + 1.0);
	return (vector3_add(vector3_scm(color3_set(1.0, 1.0, 1.0), 1.0 - t),
						vector3_scm(color3_set(0.3, 0.5, 1.0), t)
						)
			);
}

void	fill_strange(struct s_helloworld *img, const t_objects objs)
{
	const t_camera	cam = objs.camera;

	for (int j = img->height - 1; j >= 0; --j)
//	for (int j = 0; j < img->height; --j)
	{
		//printf("\33[2K\rScanlines remaining : %d", j);
		//fflush(stdout);
		for (int i = 0; i < img->width; ++i)
		{
			double	u = (double) i / (img->width - 1);
			double	v = (double) j / (img->height - 1);
			//float	r = (float) i / (img->width - 1);
			//float	g = (float) j / (img->height - 1);
			//float	b = 0.25;
			t_ray3	r = get_ray(cam, u, v);

			int	color = color3_get_color(ray_color(r, objs));
			
			printf("%d %d %d\n", color_to_red(color), color_to_green(color), color_to_blue(color));
			//printf("%d %d %d\n", (int) (r * 255.999f), (int) (g * 255.999f), (int) (b * 255.999f));
		}
	}
	//printf("\nDone.\n");
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
	const float	aspect_ratio = 16.0f / 9.0f;
	const int	width = 1080;
	const int	height = width / aspect_ratio;

	struct s_helloworld x = {width, height};
	t_objects	objects;

	objects.sphere = NULL;
	objects.camera = camera_set(16.0f / 9.0f, 2.0f, 1.0f, point3_set(0, 0, 0));

	objects.sphere = add_sphere(objects.sphere, point3_set(0, 0, -1), 0.5);
	objects.sphere = add_sphere(objects.sphere, point3_set(0, -100.5, -1), 100);
	objects.sphere = add_sphere(objects.sphere, point3_set(-1, 1, -2), 0.5);
	objects.sphere = add_sphere(objects.sphere, point3_set(1, -1, -2), 1);
	objects.sphere = add_sphere(objects.sphere, point3_set(4, 5, -5), 1);

	printf("P3\n%d %d\n255\n", width, height);
	fill_strange(&x, objects);
	
	return (0);
}
