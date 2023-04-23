/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:52:00 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/23 15:09:19 by tcakmako         ###   ########.fr       */
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
		draw_mlx_w_sampling(mlx_core->frame[0], mlx_core->objects);
	else if (keycode == KEY_ESC)
		terminate(core);
	return (0);
}

int	t_mlx_mouse_hook(int button, int x, int y, void *core)
{
	t_mlx_core		*mlx_core;
	t_point3		pos;
	t_ray3			r;
	t_hit_record	rec;

	mlx_core = core;
	if (button == 1)
		printf("x: %-5d y: %-5d\n", x, y);
	else
	{
		pos = point3_set((float) x / (mlx_core->frame[1]->width - 1),
				1 - ((float) y / (mlx_core->frame[1]->height - 1)), 0);
		r = get_ray(&mlx_core->objects->camera, pos.x, pos.y);
		if (hit_objects(&r, mlx_core->objects, &rec, set_range(0.1f, INFINITY)))
			printf("x: %-5f y: %-5f z: %-5f\n", rec.p.x, rec.p.y, rec.p.z);
		else
			printf("No object hit.\n");
	}
	return (0);
}
