/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:52:47 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/17 13:08:56 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "color3.h"

t_color3	color3_set(const float r, const float g, const float b)
{
	return (vector3_set(r, g, b));
}

void	color3_gamma2(t_color3 *c)
{
	c->x = sqrt(c->x);
	c->y = sqrt(c->y);
	c->z = sqrt(c->z);
}

int	color3_get_color(const t_color3 c)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = 255.999f * c.x;
	g = 255.999f * c.y;
	b = 255.999f * c.z;
	return ((r << 16) | (g << 8) | b);
}

t_color3	color3_add(const t_color3 c1, const t_color3 c2)
{
	t_color3	n_c;

	n_c = c1;
	n_c.x += c2.x;
	n_c.y += c2.y;
	n_c.z += c2.z;
	if (n_c.x > 1)
		n_c.x = 1;
	if (n_c.y > 1)
		n_c.y = 1;
	if (n_c.z > 1)
		n_c.z = 1;
	if (n_c.x < -1)
		n_c.x = -1;
	if (n_c.y < -1)
		n_c.y = -1;
	if (n_c.z < -1)
		n_c.z = -1;
	return (n_c);
}

t_color3	rgb_to_color3(unsigned char r, unsigned char g, unsigned char b)
{
	t_color3	color3;

	color3.x = r / 255.999f;
	color3.y = g / 255.999f;
	color3.z = b / 255.999f;
	return (color3);
}
