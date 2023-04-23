/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/23 12:57:02 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HOOK_H
# define MLX_HOOK_H

# include "keycodes.h"

# include <stdio.h>
# include "mlx.h"
# include "mlx_core.h"
# include "mlx_utils.h"

//EXTRA HEADERS ==>
//Used in key_hook and terminate function
# include "objects.h"
# include "draw_mlx.h"
// <== EXTRA HEADERS

int	terminate(void *core);
int	t_mlx_loop_hook(void *core);
int	t_mlx_key_hook(int keycode, void *core);
int	t_mlx_mouse_hook(int button, int x, int y, void *core);

#endif
