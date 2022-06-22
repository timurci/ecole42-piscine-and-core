/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:35:35 by tcakmako          #+#    #+#             */
/*   Updated: 2022/06/22 12:35:36 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		app->center_x += 100 * app->size_x / app->border;
	else if (keycode == 1)
		app->center_y -= 100 * app->size_y / app->border;
	else if (keycode == 2)
		app->center_x -= 100 * app->size_x / app->border;
	else if (keycode == 13)
		app->center_y += 100 * app->size_y / app->border;
	redraw(app);
}
