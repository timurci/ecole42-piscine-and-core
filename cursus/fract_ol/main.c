#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

char	in_circle(/*t_img *img,*/ t_mlx *app, int x, int y)
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

char	in_mandelbrot(/*t_img *img,*/ t_mlx *app, int x, int y)
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
