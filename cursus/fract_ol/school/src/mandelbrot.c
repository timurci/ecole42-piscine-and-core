/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:37:10 by tcakmako          #+#    #+#             */
/*   Updated: 2022/06/22 12:37:10 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	desat_color(int color, float factor)
{
	int	r;
	int	g;
	int	b;

	r = color & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 16) & 0xFF;
	color = 0;
	r = 9 * (1 - factor) * pow(factor, 3) * 255;
	g = 15 * pow((1 - factor), 2) * pow(factor, 2) * 255;
	b = 8.5 * pow((1 - factor), 3) * factor * 255;
	color = (color | (int) r) << 8;
	color = (color | (int) g) << 8;
	color = (color | (int) b);
	return (color * factor);
}

int	color_pixel(int itr, int max_itr)
{
	if (itr == max_itr)
		return (0x00000000);
	else
		return (desat_color(0x00a1b2c3, (float) itr / max_itr));
}

static int	apply_mandel(double *c, int max_iter)
{
	int		itr;
	double	z[2];
	double	z2[2];

	itr = 0;
	z[0] = 0;
	z[1] = 0;
	z2[0] = 0;
	z2[1] = 0;
	while (z2[0] + z2[1] < 4 && ++itr < max_iter)
	{
		z[1] = (z[0] + z[0]) * z[1] + c[1];
		z[0] = z2[0] - z2[1] + c[0];
		z2[0] = z[0] * z[0];
		z2[1] = z[1] * z[1];
	}
	return (color_pixel(itr, max_iter));
}

void	mandelbrot(t_mlx *app, t_img *img)
{
	int		pos[2];
	double	c[2];
	double	scale;

	scale = (double) 1 / app->border;
	pos[1] = 0;
	while (pos[1] < app->size_y)
	{
		pos[0] = 0;
		while (pos[0] < app->size_x)
		{
			c[0] = (double)(pos[0] - app->center_x) * scale;
			c[1] = (double)(app->center_y - pos[1]) * scale;
			fill_bits(img, pos[0], pos[1], apply_mandel(c, app->max_iter));
			pos[0]++;
		}
		pos[1]++;
	}
}
