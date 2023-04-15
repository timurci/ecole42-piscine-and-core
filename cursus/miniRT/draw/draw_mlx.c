/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:43 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 14:23:54 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_mlx.h"

static t_color3	ray_color(t_ray3 *r, const t_objects *objs, const int depth)
{
	t_hit_record	rec;
	//float			t;
	t_point3		target;

	if (depth <= 0)
		return (color3_set(0, 0, 0));

	if (hit_objects(r, objs, &rec, set_range(0.001, INFINITY)))
	{
		target = vector3_add(rec.n, vector3_unit(vector3_random_minmax(-1, 1)));
		ray3ppp_set(r, &rec.p, &target);
		t_color3	reflected = vector3_ewm(ray_color(r, objs, depth - 1),
									rec.c);

		t_color3	diff_intensity;
		float		light_factor = point_light_factor(&objs->point_light, &rec);

		if (light_factor > 0 &&
				hit_any(point_to_light(&objs->point_light, &rec.p), objs,
						set_range(0.001, INFINITY)))
			color3p_set(&diff_intensity, 0, 0, 0);
		else
			diff_intensity = vector3_scm(objs->point_light.c, light_factor);
		if (depth < 5)
			reflected = vector3_ewm(objs->ambient_light.c, rec.c);
		return (vector3_add(reflected, diff_intensity));
	}

	//t_vec3	unit_dir = vector3_unit(r.direction);
	
	//t = 0.5 * (unit_dir.y + 1.0f);
	//return (vector3_add(vector3_scm(color3_set(1.0, 1.0, 1.0), 1.0 - t),
	//					vector3_scm(color3_set(0.3, 0.5, 1.0), t)
	//					)
	//		);
	
	// AMBIENT LIGHTING CONCEPT
	
	//t = 0.5f * (unit_dir.x + 0.5f);
	//t = 0.1f;
	
	//const t_color3	ambient = vector3_scm(color3_set(0.3f, 0.5f, 1.0f), t);
	//return (ambient);
	return (objs->ambient_light.c);
}

static t_color3	average_color(t_mlx_image *img, const t_objects *objs,
						const int i, const int j)
{
	t_color3	color;
	float		u;
	float		v;
	t_ray3		r;

	color3p_set(&color, 0, 0, 0);

	//if (SAMPLES_PER_PIXEL == 1)
	//{
	//	u = (float) i / (img->width - 1);
	//	v = (float) j / (img->height - 1);
	//	r = get_ray(&objs->camera, &u, &v);
	//	color = ray_color(&r, objs, 1);
	//	color.x = sqrt(color.x);
	//	color.y = sqrt(color.y);
	//	color.z = sqrt(color.z);

	//	return (color);
	//}

	for (int s = 0; s < SAMPLES_PER_PIXEL; ++s)
	{
		u = (i + ((float) rand() / ((long) RAND_MAX + 1))) / (img->width - 1);
		v = (j + ((float) rand() / ((long) RAND_MAX + 1))) / (img->height - 1);
		r = get_ray(&objs->camera, &u, &v);
		color = vector3_add(color, ray_color(&r, objs, MAX_DEPTH));
	}

	color = vector3_scm(color, 1.0f / SAMPLES_PER_PIXEL);
	color3_gamma2(&color);

	return (color);
}

void	draw_mlx_w_sampling(t_mlx_image *img, const t_objects *objs)
{
	printf("\n");
	for (int j = img->height - 1; j >= 0; --j)
	//for (int j = 0; j < img->height; ++j)
	{
		//fprintf(stderr, "\33[2K\rScanlines remaining : %d", j);
		printf("\33[1F\33[2KScanlines remaining : %d\n", j);
		//fflush(stdout);
		for (int i = 0; i < img->width; ++i)
		{
			t_color3	rand_color = average_color(img, objs, i, j);
			int			color = color3_get_color(rand_color);
			
			t_mlx_image_set_pixel(img, i, (img->height - j), color);
			//printf("%d %d %d\n", color_to_red(color), color_to_green(color), color_to_blue(color));
			//printf("%d %d %d\n", (int) (r * 255.999f), (int) (g * 255.999f), (int) (b * 255.999f));
		}
	}
	printf("Rendering complete!\n\n");
}

void	draw_mlx_wo_sampling(t_mlx_image *img, const t_objects *objs)
{
	t_color3	color3;
	int			color;
	float		u;
	float		v;
	t_ray3		r;

	printf("\n");
	for (int j = img->height - 1; j >= 0; --j)
	{
		printf("\33[1F\33[2KScanlines remaining : %d\n", j);
		for (int i = 0; i < img->width; ++i)
		{
			u = (float) i / (img->width - 1);
			v = (float) j / (img->height - 1);
			r = get_ray(&objs->camera, &u, &v);
			color3 = ray_color(&r, objs, 1);
			color3_gamma2(&color3);
			color = color3_get_color(color3);
			t_mlx_image_set_pixel(img, i, (img->height - j), color);
		}
	}
	printf("Rendering complete!\n\n");
}

