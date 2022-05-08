#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char	*ft_strdup(char *s);

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

void	replace_bg(t_mlx *app, int color)
{
	t_img	*img;
	t_img	*temp;

	img = malloc(sizeof(*img));
	img->ptr = mlx_new_image(app->mlx, app->size_x, app->size_y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_line, &img->end);
	paint_bg(img, app, color);
	temp = app->frame;
	app->frame = img;
	mlx_destroy_image(app->mlx, img->ptr);
	free(temp);
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
	paint_bg(img, app, 0x00a1b2c3);
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

int	color_bit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - 48);
	else if (c >= 'a' && c <= 'f')
		return (c - 87);
	else if (c >= 'A' && c <= 'F')
		return (c - 55);
	return (0);
}

int	get_color(void)
{
	int		color;
	int		scan;
	char	buf[7];

	printf("ENTER HEX VALUE (ex. fb2ab1): ");
	read(0, buf, 6);
	buf[6] = 0;
	color = 0;
	scan = 0;
	while (scan < 6)
	{
		color |= color_bit(buf[scan]);
		color = color << 1;
		scan++;
	}
	return (color);
}

int	key_handler(int keycode, void *param)
{
	t_mlx *app;
	//int	colors[] = {0x00FFFFFF, 0x00000000};

	app = (t_mlx *) param;
	//printf("\x1b[1F\r\x1b[0K%d\n", keycode);
	if (keycode == 44)
	{
		get_color();
		mlx_put_image_to_window(app->mlx, app->win, app->frame, 0, 0);
	}
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
