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

char	*ft_strdup(char *s);
char	in_circle(t_img *img, t_mlx *app, int x, int y);
char	in_mandelbrot(t_img *img, t_mlx *app, int x, int y);
void	mandelbrot(float *real, float *imgry, float dx, float dy);
void	draw_item(t_mlx *app, char (*f)(t_img *, t_mlx *, int, int), int *clrs);

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

int		call_item(t_mlx *app, char (*f)(t_img *, t_mlx *, int, int), char mode)
{
	int	colors[] = {0x00FFFFFF, 0x00000000};

	app->border = 100;
	app->offset_x = 0;
	app->offset_y = 0;
	app->mode = mode;
	draw_item(app, f, colors);
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
	{
		app->border -= 50;
		//app->offset_x -= sign(app->size_x / 2 + app->offset_x - x) * 0.25;
		//app->offset_y -= sign(app->size_y / 2 + app->offset_y - y) * 0.25;
	}
	if (app->mode == 9)
		draw_item(app, in_circle, colors);
	else if (app->mode == 1)
		draw_item(app, in_mandelbrot, colors);
	return (1);
}

int	key_handler(int keycode, void *param)
{
	t_mlx *app;
	int	colors[] = {0x00FFFFFF, 0x00000000};

	app = (t_mlx *) param;
	//printf("\x1b[1F\r\x1b[0K%d\n", keycode);
	if (keycode == 65307)
		destroy_win(app);
	else if (keycode == 49 + 8)
		call_item(app, in_circle, 9);
	else if (keycode == 49)
		call_item(app, in_mandelbrot, 1);
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
}

int	put_frame(void *param)
{
	t_mlx	*app;

	app = (t_mlx *) param;
	if (app->is_modified)
	{
		mlx_put_image_to_window(app->mlx, app->win, app->frame->ptr, 0, 0);
		app->is_modified--;
	}
	return (1);
}

char	in_circle(t_img *img, t_mlx *app, int x, int y)
{
	float	dx;
	float	dy;
	int		origin_x;
	int		origin_y;

	origin_x = app->size_x / 2 + app->offset_x;
	origin_y = app->size_y / 2 + app->offset_y;
	if (x < origin_x - app->border || x > origin_x + app->border
		|| y < origin_y - app->border || y > origin_y + app->border)
		return (0);
	//if (x < 0 || x > app->size_x || y < 0 || y > app->size_y)
	//	return (0);
	dx = (float) (x - origin_x) / app->border;
	dy = (float) (y - origin_y) / app->border;
	if (dx * dx + dy * dy <= 1)
		return (1);
	return (0);
}

void	mandelbrot(float *real, float *imgry, float dx, float dy)
{
	float	x_sq;
	float	two_xy;
	float	y_sq;

	x_sq = *real * *real;
	y_sq = *imgry * *imgry * -1;
	if (*imgry)
		two_xy = 2 * *real * *imgry;
	else
		two_xy = 0;
	*real = x_sq + y_sq + dx;
	*imgry = two_xy + dy;
}

char	in_mandelbrot(t_img *img, t_mlx *app, int x, int y)
{
	float	dx;
	float	dy;
	int		origin_x;
	int		origin_y;
	float	im;
	float	real;
	int		scan;

	origin_x = app->size_x / 2 + app->offset_x;
	origin_y = app->size_y / 2 + app->offset_y;
	if (x < origin_x - app->border || x > origin_x + app->border
		|| y < origin_y - app->border || y > origin_y + app->border)
		return (0);
	//if (x > app->size_x || x < 0 || y > app->size_y || y < 0)
	//	return (0);
	dx = (float) (x - origin_x) / app->border * 2;
	dy = (float) (y - origin_y) / app->border * 2;
	scan = 0;
	real = dx;
	im = dy;
	while (scan++ < 100)
	{
		mandelbrot(&real, &im, dx, dy);
		if (real < -2 || real > 2 || im < -2 || im > 2)
			return (0);
	}
	return (1);
}

/*void	draw_item(t_mlx *app, char (*f)(t_img *, t_mlx *, int, int), int *clrs)
{
	t_img	*img;
	t_img	*temp;
	int	x;
	int	y;

	img = malloc(sizeof(*img));
	img->ptr = mlx_new_image(app->mlx, app->size_x, app->size_y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_line, &img->end);
	paint_bg(img, app, clrs[0]);
	y = app->size_y / 2 + app->offset_y - app->border;
	while (y < app->size_y / 2 + app->offset_y + app->border)
	{
		x = app->size_x / 2 + app->offset_x - app->border;
		while (x < app->size_x / 2 + app->offset_x + app->border)
		{
			if ((*f)(img, app, x, y))
				fill_bits(img, x, y, clrs[1]);
			x++;
		}
		y++;
	}
	temp = app->frame;
	app->frame = img;
	mlx_destroy_image(app->mlx, temp->ptr);
	free(temp);
}*/

void	draw_item(t_mlx *app, char (*f)(t_img *, t_mlx *, int, int), int *clrs)
{
	t_img	*img;
	t_img	*temp;
	int	x;
	int	y;

	img = malloc(sizeof(*img));
	img->ptr = mlx_new_image(app->mlx, app->size_x, app->size_y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_line, &img->end);
	paint_bg(img, app, clrs[0]);
	y = 0;
	while (y < app->size_y)
	{
		x = 0;
		while (x < app->size_x)
		{
			if ((*f)(img, app, x, y))
				fill_bits(img, x, y, clrs[1]);
			x++;
		}
		y++;
	}
	temp = app->frame;
	app->frame = img;
	mlx_destroy_image(app->mlx, temp->ptr);
	free(temp);
}

int	activate_frame(void *param)
{
	t_mlx	*app;

	app = (t_mlx *) param;
	app->is_modified = 100;
}

int	main(void)
{
	t_mlx	app;

	app.mlx = mlx_init();
	set_mlx(&app);
	//draw_item(&app, in_circle, colors);
	app.win = mlx_new_window(app.mlx, app.size_x, app.size_y, app.title);
	mlx_key_hook(app.win, key_handler, &app);
	mlx_mouse_hook(app.win, mouse_handler, &app);
	mlx_hook(app.win, 17, 0, destroy_win, &app);
	mlx_hook(app.win, 15, 1L<<16, activate_frame, &app);
	mlx_loop_hook(app.mlx, put_frame, &app);
	mlx_loop(app.mlx);
	return (0);
}
