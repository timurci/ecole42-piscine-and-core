/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:00:56 by tcakmako          #+#    #+#             */
/*   Updated: 2022/06/20 12:25:04 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	call_item(t_mlx *app, void (*f)(t_mlx *, t_img *), char mode)
{
	app->border = 100;
	app->center_x = app->size_x / 2;
	app->center_y = app->size_y / 2;
	app->mode = mode;
	draw_item(app, f);
}

void	draw_item(t_mlx *app, void (*f)(t_mlx *, t_img *))
{
	t_img	*img;
	t_img	*temp;

	img = malloc(sizeof(*img));
	img->ptr = mlx_new_image(app->mlx, app->size_x, app->size_y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_line, &img->end);
	(*f)(app, img);
	temp = app->frame;
	app->frame = img;
	mlx_destroy_image(app->mlx, temp->ptr);
	free(temp);
	app->is_modified = 100;
}

void	redraw(t_mlx *app)
{
	if (app->mode == 9)
		draw_item(app, circle);
	else if (app->mode == 1)
		draw_item(app, mandelbrot);
	else if (app->mode == 2)
		draw_item(app, julia);
}
