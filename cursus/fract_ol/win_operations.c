#include "fractol.h"

void	set_mlx(t_mlx *app)
{
	t_img	*img;

	app->size_x = 1080;
	app->size_y = 768;
	app->title = ft_strdup("Fract'ol");
	app->border = 200;
	app->mode = 0;
	app->colors = init_color_palette();
	img = malloc(sizeof(*img));
	img->ptr = mlx_new_image(app->mlx, app->size_x, app->size_y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_line, &img_end);
	paint_bg(img, app, 0x00FFFFFF);
	app->frame = img;
}

// 2 palettes with 2 values: 1. background 2. foreground

int	**init_color_palette(void)
{
	app->colors = malloc(sizeof(int *) * 2);
	app->colors[0] = malloc(sizeof(int) * 2);
	app->colors[0][0] = 0x00000000;
	app->colors[0][1] = 0x00FFFFFF;
	app->colors[1] = malloc(sizeof(int) * 2);
	app->colors[1][0] = 0x003271a8;
	app->colors[1][1] = 0x00cf9538;
}

int	destroy_win(void *param)
{
	mlx_destroy_window(((t_mlx *) param)->mlx, ((t_mlx *) param)->win);
	exit(EXIT_SUCCESS);
}

void	fill_bits(t_img *img, int x, int y, int color)
{
	char	*addr;

	addr = img->data + y * img->s_line;
	if (!img->end)
		addr += x * img->bpp / 8;
	else
		addr += ((x + 1) * img->bpp / 8) - 1;
	*(unsigned int *) addr = color;
}
