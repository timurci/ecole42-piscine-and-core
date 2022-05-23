/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:00:37 by tcakmako          #+#    #+#             */
/*   Updated: 2022/05/23 17:10:40 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handler(int keycode, void *param)
{
	t_mlx	*app;

	app = (t_mlx *) param;
	//printf("\x1b[1F\r\x1b[0K%d\n", keycode);
	if (keycode == 53)
		destroy_win(app);
	else if (keycode == 25)
		call_item(app, circle, 9);
	else if (keycode == 18)
		call_item(app, mandelbrot, 1);
	else if (keycode == 12 || keycode == 14)
		change_itr(app, keycode);
	else if (keycode == 13 || (keycode > -1 && keycode < 4))
		shift_item(app, keycode);
	else if (keycode == 44)
		printf("Border: %5zu\tCx: %5d\tCy: %5d\n", app->border, app->center_x, app->center_y);
	return (1);
}

int	mouse_handler(int button, int x, int y, void *param)
{
	t_mlx	*app;

	app = (t_mlx *) param;
	app->mouse_x = x;
	app->mouse_y = y;
	if (button == 1)
		printf("x: %4d\ty: %4d\n", x, y);
	else if (button == 4 || button == 5)
		zoom_handler(app, button, x, y);
	return (1);
}

int	zoom_handler(t_mlx *app, int button, int x, int y)
{
	//int	mov_x;
	//int	mov_y;

	//mov_x = sign(x - app->size_x / 2);
	//mov_y = sign(y - app->size_y / 2);
	if (app->mode == 0)
		return (0);
	if (button == 4 && app->border < 2147483597)
	{
		app->border *= 1.1;
		app->center_x -= (float) /*sign(x - mid_x)*/ 1;
		app->center_y -= (float) /*sign(y - mid_y)*/ 1;
	}
	else if (app->border > 50)
	{
		app->border /= 1.1;
		app->center_x += (float) /*sign(x - mid_x) / app->border **/x * 5000;
		app->center_y += (float) /*sign(y - mid_y) / app->border **/y * 5000;
	}
	redraw(app);
	return (1);
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

int	activate_frame(void *param)
{
	((t_mlx *) param)->is_modified = 100;
	return (1);
}
