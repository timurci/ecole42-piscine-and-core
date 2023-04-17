/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color3.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/17 13:06:21 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR3_H
# define COLOR3_H

# include "vector3.h"
# include <math.h>

typedef t_vec3	t_color3;

//scaled rgb values [0,1]
t_color3	color3_set(const float r, const float g, const float b);
t_color3	color3_add(const t_color3 c1, const t_color3 c2);

void		color3_gamma2(t_color3 *c);

t_color3	rgb_to_color3(unsigned char r, unsigned char g, unsigned char b);

//returns 255.999 * {r,g,b}
int			color3_get_color(const t_color3 c);

#endif
