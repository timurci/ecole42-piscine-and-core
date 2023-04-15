/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:55 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:51:55 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_core.h"

//init
t_mlx_core	*t_mlx_init_core(int size_x, int size_y, char *title)
{
	t_mlx_core	*core;

	core = malloc(sizeof(*core));
	core->ptr = mlx_init();
	if (title)
		core->win = mlx_new_window(core->ptr, size_x, size_y, title);
	else
		core->win = mlx_new_window(core->ptr, size_x, size_y, "miniRT");
	core->width = size_x;
	core->height = size_y;
	core->frame[0] = t_mlx_init_image(core, size_x, size_y);
	core->frame[1] = t_mlx_init_image(core, size_x, size_y);
	core->frame_repeat = 0;
	return (core);
}

t_mlx_image	*t_mlx_init_image(t_mlx_core *core, int size_x, int size_y)
{
	t_mlx_image	*img;

	img = malloc(sizeof(*img));
	img->ptr = mlx_new_image(core->ptr, size_x, size_y);
	img->width = size_x;
	img->height = size_y;
	img->data = mlx_get_data_addr(img->ptr, &img->bbp,
			&img->size_line, &img->endian);
	return (img);
}

//destroy
void	t_mlx_destroy_core(t_mlx_core *core)
{
	mlx_destroy_window(core->ptr, core->win);
	mlx_destroy_image(core->ptr, core->frame[0]->ptr);
	mlx_destroy_image(core->ptr, core->frame[1]->ptr);
	free(core->frame[0]);
	free(core->frame[1]);
	free(core);
}

//misc
void	t_mlx_core_switch_frame(t_mlx_core *core)
{
	void	*p;

	p = core->frame[1];
	core->frame[1] = core->frame[0];
	core->frame[0] = p;
	core->frame_repeat = 1;
}
