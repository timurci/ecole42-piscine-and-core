/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:01:30 by tcakmako          #+#    #+#             */
/*   Updated: 2022/05/07 18:19:27 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
