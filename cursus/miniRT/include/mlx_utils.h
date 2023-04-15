/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:59:00 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "mlx.h"
# include "mlx_core.h"

void	t_mlx_image_set_pixel(t_mlx_image *img, int x, int y, int color);
void	t_mlx_bg_set_pixel(t_mlx_core *core, int x, int y, int color);

//color
int		color_to_red(int color);
int		color_to_green(int color);
int		color_to_blue(int color);
int		rgb_to_color(unsigned char r, unsigned char g, unsigned char b);

#endif
