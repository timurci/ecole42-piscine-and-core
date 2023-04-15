/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:52:47 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:52:47 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray3.h"

t_ray3	ray3_set(t_point3 origin, t_vec3 direction)
{
	t_ray3	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_ray3	*copy_ray3(const t_ray3 r)
{
	t_ray3	*p;

	p = malloc(sizeof(*p));
	*p = r;
	return (p);
}

void	ray3ppp_set(t_ray3 *ray_p, const t_point3 *origin,
					const t_vec3 *direction)
{
	ray_p->origin = *origin;
	ray_p->direction = *direction;
}

t_point3	ray3_tpos(const t_ray3 *r, const float t)
{
	return (vector3_add(r->origin, vector3_scm(r->direction, t)));
}
