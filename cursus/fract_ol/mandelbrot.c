#include "fractol.h"

static int	desat_color(int color, int factor)
{
	int	r;
	int	g;
	int	b;

	r = color & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 16) & 0xFF;
	color = 0;
	color = (color | (b * factor)) << 8;
	color = (color | (g * factor)) << 8;
	color = (color | (r * factor)) << 8;
	return (color);
}

int	color_pixel(int itr)
{
	if (itr > 900)
		return (0x00000000);
	else
		return (desat_color(0x00a1b2c3, itr / 2));
}

static int	apply_mandel(double x0, double y0)
{
	int		itr;
	double	x;
	double	y;
	double	x2;
	double	y2;

	itr = 0;
	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0;
	while (x2 + y2 < 4 && itr++ < 1000)
	{
		y = (x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	return (color_pixel(itr));
}

void	mandelbrot(t_mlx *app, t_img *img)
{
	int		pos[2];
	double	scaled[2];
	double	scale;

	scale = (double) 1 / app->border;
	pos[1] = 0;
	while (pos[1] < app->size_y)
	{
		pos[0] = 0;
		while (pos[0] < app->size_x)
		{
			scaled[0] = (pos[0] - app->center_x) * scale;
			scaled[1] = (app->center_y - pos[1]) * scale;
			fill_bits(img, pos[0], pos[1], apply_mandel(scaled[0], scaled[1]));
			pos[0]++;
		}
		pos[1]++;
	}
}
