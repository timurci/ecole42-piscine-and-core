/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:52:00 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 14:20:41 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_hook.h"

//EXTRA HEADERS ==>
//Used in key_hook, terminate function
#include "objects.h"
#include "draw_mlx.h"
// <== EXTRA HEADERS

int	terminate(void *core)
{
	t_mlx_core	*mlx_core;

	mlx_core = core;
	destroy_objects(mlx_core->objects);
	free(mlx_core->objects);
	t_mlx_destroy_core(core);
	exit(EXIT_SUCCESS);
	return (0);
}

int	t_mlx_loop_hook(void *param)
{
	t_mlx_core	*core;

	core = param;
	if (core->frame_repeat)
	{
		mlx_put_image_to_window(core->ptr, core->win,
			core->frame[1]->ptr, 0, 0);
		--core->frame_repeat;
	}
	return (0);
}

int	t_mlx_key_hook(int keycode, void *core)
{
	t_mlx_core	*mlx_core;

	mlx_core = core;
	if (keycode == KEY_1)
	{
		t_mlx_core_switch_frame(mlx_core);
		printf("Frame switched\n");
	}
	else if (keycode == KEY_2)
		draw_mlx_w_sampling(mlx_core->frame[1], mlx_core->objects);
	else if (keycode == KEY_ESC)
		terminate(core);
	return (0);
}
