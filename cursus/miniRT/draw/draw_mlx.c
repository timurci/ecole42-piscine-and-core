/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:43 by tcakmako          #+#    #+#             */
/*   Updated: 2023/05/22 14:40:16 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_mlx.h"

static t_color3	ray_color(t_ray3 *r, const t_objects *objs, const int depth)
{
	t_hit_record	rec;
	t_point3		target;
	t_color3		reflected;
	t_color3		diff_intensity;
	float			light_factor;

	if (depth <= 0)
		return (objs->ambient_light.c);
	if (hit_objects(r, objs, &rec, set_range(0.001, INFINITY)))
	{
		target = vector3_add(rec.n, vector3_unit(vector3_random_minmax(-1, 1)));
		ray3ppp_set(r, &rec.p, &target);
		reflected = vector3_ewm(ray_color(r, objs, depth - 1), rec.c);
		light_factor = point_light_factor(&objs->point_light, &rec);
		if (light_factor < 0 || (light_factor > 0
				&& hit_any(point_to_light(&objs->point_light, &rec.p), objs,
					set_range(0.001, INFINITY))))
			diff_intensity = color3_set(0, 0, 0);
		else
			diff_intensity = vector3_scm(objs->point_light.c, light_factor);
		if (depth < 5)
			reflected = vector3_ewm(objs->ambient_light.c, rec.c);
		return (vector3_add(reflected, diff_intensity));
	}
	return (objs->ambient_light.c);
}

static t_color3	average_color(t_mlx_image *img, const t_objects *objs,
						const int i, const int j)
{
	t_color3	color;
	float		u;
	float		v;
	t_ray3		r;
	int			s;

	color = color3_set(0, 0, 0);
	s = 0;
	while (s++ < SAMPLES_PER_PIXEL)
	{
		u = (i + ((float) rand() / ((long) RAND_MAX + 1))) / (img->width - 1);
		v = (j + ((float) rand() / ((long) RAND_MAX + 1))) / (img->height - 1);
		r = get_ray(&objs->camera, u, v);
		color = vector3_add(color, ray_color(&r, objs, MAX_DEPTH));
	}
	color = vector3_scm(color, 1.0f / SAMPLES_PER_PIXEL);
	color3_gamma2(&color);
	return (color);
}

void	draw_mlx_w_sampling(t_mlx_image *img, const t_objects *objs)
{
	t_color3	rand_color;
	int			color;
	int			i;
	int			j;

	j = img->height - 1;
	printf("\n");
	while (--j >= 0)
	{
		i = 0;
		printf("\33[1F\33[2KScanlines remaining : %d\n", j);
		while (++i < img->width)
		{
			rand_color = average_color(img, objs, i, j);
			color = color3_get_color(rand_color);
			t_mlx_image_set_pixel(img, i, (img->height - j - 1), color);
		}
	}
	printf("\e[0;32mRendering complete!\e[0m\n");
}

void	draw_mlx_wo_sampling(t_mlx_image *img, const t_objects *objs)
{
	t_color3	color3;
	t_ray3		r;
	int			i;
	int			j;

	j = img->height - 1;
	printf("\n");
	while (j >= 0)
	{
		i = 0;
		printf("\33[1F\33[2KScanlines remaining : %d\n", j);
		while (++i < img->width)
		{
			r = get_ray(&objs->camera,
					(float) i / (img->width - 1),
					(float) j / (img->height - 1));
			color3 = ray_color(&r, objs, 1);
			color3_gamma2(&color3);
			t_mlx_image_set_pixel(img, i, (img->height - j - 1),
				color3_get_color(color3));
		}
		--j;
	}
	printf("\e[0;32mRendering complete!\e[0m\n");
}
