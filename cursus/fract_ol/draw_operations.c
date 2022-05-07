/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:00:56 by tcakmako          #+#    #+#             */
/*   Updated: 2022/05/07 18:13:15 by tcakmako         ###   ########.fr       */
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
	app->border = 100;
	app->offset_x = 0;
	app->offset_y = 0;
	app->mode = mode;
	draw_item(app, f);
}

void	draw_item(t_mlx *app, void (*f)(t_mlx *, t_img *))
{
	t_img	*img;
	t_img	*temp;
	int		x;
	int		y;

	img = malloc(sizeof(*img));
	img->ptr = mlx_new_image(app->mlx, app->size_x, app->size_y);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->s_line, &img->end);
	(*f)(app, img);
	temp = app->frame;
	app->frame = img;
	mlx_destroy_image(app->mlx, temp->ptr);
	free(temp);
}

void	vector_init(t_vector *v)
{
	v->dir_x = 1;
	v->dir_y = 1;
	v->pos_x = 0;
	v->pos_y = 0;
}
