/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:35:30 by tcakmako          #+#    #+#             */
/*   Updated: 2022/05/08 11:36:43 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int	main(void)
{
	t_mlx	app;

	app.mlx = mlx_init();
	set_mlx(&app);
	app.win = mlx_new_window(app.mlx, app.size_x, app.size_y, app.title);
	mlx_key_hook(app.win, key_handler, &app);
	mlx_mouse_hook(app.win, mouse_handler, &app);
	mlx_hook(app.win, 17, 0, destroy_win, &app);
	mlx_hook(app.win, 15, 1L << 16, activate_frame, &app);
	mlx_loop_hook(app.mlx, put_frame, &app);
	mlx_loop(app.mlx);
	return (0);
}
