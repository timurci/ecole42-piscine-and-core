#include "fractol.h"

void	change_itr(t_mlx *app, int keycode)
{
	if (keycode == 12)
	{
		if (app->max_iter < 50)
			app->max_iter += 1;
		else
			app->max_iter *= 1.05;
	}
	else
	{
		if (app->max_iter > 50)
			app->max_iter *= 0.95;
		else
			app->max_iter -= 1;
	}
	redraw(app);
}

void	shift_item(t_mlx *app, int keycode)
{
	if (keycode == 0)
		app->center_x += 10 * app->border / app->size_x;
	else if (keycode == 1)
		app->center_y -= 10 * app->border / app->size_y;
	else if (keycode == 2)
		app->center_x -= 10 * app->border / app->size_x;
	else if (keycode == 13)
		app->center_y += 10 * app->border / app->size_y;
	redraw(app);
}
