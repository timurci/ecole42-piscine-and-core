#include "fractol.h"

static int	in_circle(t_mlx *app, int x, int y)
{
	x = (x - (app->size_x / 2));
	y = ((app->size_y / 2) - y);
	if ((size_t) x * x + y * y < app->border)
		return (0x00000000);
	else
		return (0x00FFFFFF);
}

void	circle(t_mlx *app, t_img *img)
{
	int		x;
	int		y;
	int		pixel_size;
	
	pixel_size = app->border * 2 / app->size_x;
	y = 0;
	while (y < app->size_y / 2)
	{
		x = 0;
		while (x < app->size_x)
		{
			fill_bits(img, x, y, in_circle(app, x, y));
			x++;
		}
		y++;
	}
	//fill_other_half(app, img);
}
