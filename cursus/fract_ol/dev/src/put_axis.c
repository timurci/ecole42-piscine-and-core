#include "fractol.h"

void	put_axis(t_mlx *app)
{
	int	x;
	int	y;

	if (app->center_y < app->size_y && app->center_y > 0)
	{
		x = 0;
		y = app->center_y;
		while (x < app->size_x)
			fill_bits(app->frame, x++, y, 0x00c4c4c4);
	}
	if (app->center_x < app->size_x && app->center_x > 0)
	{
		y = 0;
		x = app->center_x;
		while (y < app->size_y)
			fill_bits(app->frame, x, y++, 0x00c4c4c4);
	}
}
