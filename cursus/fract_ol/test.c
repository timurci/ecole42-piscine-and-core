#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		s_line;
	int		end;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	char	*title;
	t_img	*frame;
	char	is_modified;
	char	mode;
	int		size_x;
	int		size_y;
	int		mouse_x;
	int		mouse_y;
	int		border;
	int		offset_x;
	int		offset_y;
}				t_mlx;

void	fill_bits(t_img *img, int x, int y, int color)
{
	char	*addr;

	addr = img->data + y * img->s_line;
	if (!img->end)
		addr += x * img->bpp / 8;
	else
		addr += ((x + 1) * img->bpp / 8) - 1;
	*(unsigned int *)addr = color;
}

void	paint_bg(t_img *img, t_mlx *app, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->size_y)
	{
		x = 0;
		while (x < app->size_x)
		{
			fill_bits(img, x, y, color);
			x++;
		}
		y++;
	}
	app->is_modified = 100;
}

void	set_mlx(t_mlx *app)
{
	t_img	*img;

	app->size_x = 1080;
	app->size_y = 768;
	app->title = ft_strdup("My Awesome Application!");
	app->border = 200;
	app->mode = 0;
	img = malloc(sizeof(*img));
	img->ptr = mlx_new_image(app->mlx, app->size_x, app->size_y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_line, &img->end);
	paint_bg(img, app, 0x00FFFFFF);
	app->frame = img;
}

int	destroy_win(void *app)
{
	mlx_destroy_window(((t_mlx *)app)->mlx, ((t_mlx *)app)->win);
	exit(EXIT_SUCCESS);
}

int	sign(int n)
{
	if (n < 0)
		return (-1);
	else
		return (1);
}

int	zoom_handler(t_mlx *app, int button, int x, int y)
{
	int	colors[] = {0x00FFFFFF, 0x00000000};

	if (app->mode == 0)
		return (0);
	if (button == 4 && app->border < 2147483597)
	{
		app->border += 50;
		app->offset_x += sign(app->size_x / 2 - x) * 20;
		app->offset_y += sign(app->size_y / 2 - y) * 20;
	}
	else if (app->border > 50)
		app->border -= 50;
	if (app->mode == 9)
		draw_item(app, in_circle, colors);
	else if (app->mode == 1)
		draw_item(app, in_mandelbrot, colors);
	return (1);
}

int	key_handler(int keycode, void *param)
{
	t_mlx *app;
	//int	colors[] = {0x00FFFFFF, 0x00000000};

	app = (t_mlx *) param;
	printf("\x1b[1F\r\x1b[0K%d\n", keycode);
	return (1);
}

int	mouse_handler(int button, int x, int y, void *param)
{
	t_mlx *app;

	app = (t_mlx *) param;
	app->mouse_x = x;
	app->mouse_y = y;
	if (button == 1)
		printf("x: %4d\ty: %4d\n", app->mouse_x, app->mouse_y);
	else if (button == 4 || button == 5)
		zoom_handler(app, button, x, y);
	return (1);
}

int	main(void)
{
	t_mlx	app;

	app.mlx = mlx_init();
	set_mlx(&app);
	app.win = mlx_new_window(app.mlx, app.size_x, app.size_y, app.title);
	mlx_key_hook(app.win, key_handler, &app);
	mlx_mouse_hook(app.win, mouse_handler, &app);
	mlx_hook(app.win, 17, 0, destroy_win, &app);
	mlx_loop(app.mlx);
	return (0);
}
