#include "fractol.h"

void	paint_bg(t_img *img, t_mlx *app, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->size_y)
	{
		x = 0;
		while (x < app->size x)
		{
			fill_bits(img, x, y, color);
			x++;
		}
		y++;
	}
	app->is_modified = 100;
}

void	call_item(t_mlx *app, char (*f)(t_mlx *, int, int), char mode)
{
	int	colors[] = {0x00FFFFFF, 0x00000000};

	app->border = 100;
	app->offset_x = 0;
	app->offset_y = 0;
	app->mode = mode;
	draw_item(app, f, colors);
}

void	draw_item(t_mlx *app, void (*f)(t_mlx *, t_img *))
{
	t_img	*img;
	t_img	*temp;
	int	x;
	int	y;

	img	= malloc(sizeof(*img));
	img->ptr = mlx_new_image(app->mlx, app->size_x, app->size_y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_line, &img->end);
	(*f)(app, img);
	temp = app->frame;
	app->frame = img;
	mlx_destroy_image(app->mlx, temp->ptr);
	free(temp);
}
