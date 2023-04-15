/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:57 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:57:08 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	t_mlx_image_set_pixel(t_mlx_image *img, int x, int y, int color)
{
	unsigned int	*dst;

	dst = (unsigned int *) &img->data[y * img->size_line + (x * img->bbp / 8)];
	*dst = color;
}

void	t_mlx_bg_set_pixel(t_mlx_core *core, int x, int y, int color)
{
	t_mlx_image_set_pixel(core->frame[0], x, y, color);
}
