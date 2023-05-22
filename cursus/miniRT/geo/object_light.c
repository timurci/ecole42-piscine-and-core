/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:40 by tcakmako          #+#    #+#             */
/*   Updated: 2023/05/22 22:57:04 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_light.h"

t_light_p	set_point_light(const t_color3 c, const float i, const t_point3 p)
{
	t_light_p	light;

	light.c = vector3_scm(c, i);
	light.p = p;
	return (light);
}

t_light_a	set_ambient_light(const t_color3 c, const float i)
{
	t_light_a	light;

	light.c = vector3_scm(c, i);
	return (light);
}

float	point_light_factor(const t_light_p *l, const t_hit_record *r)
{
	const t_vec3	lv = point_to_light(l, &r->p).direction;
	const float		lv_length_sq = vector3_length_squared(lv);

	return (vector3_dtp(r->n,
			lv) / (vector3_length(r->n) * lv_length_sq));
}

t_ray3	point_to_light(const t_light_p *l, const t_point3 *p)
{
	t_ray3	r;

	r.origin = *p;
	r.direction = vector3_add(l->p, vector3_scm(*p, -1));
	return (r);
}
