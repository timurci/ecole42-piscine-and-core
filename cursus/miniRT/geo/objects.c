/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:40 by tcakmako          #+#    #+#             */
/*   Updated: 2023/05/22 22:57:40 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_sphere.h"
#include "objects.h"

//it is an abbreviation for iterator
typedef struct s_utils
{
	t_hit_record	rec;
	bool			hit;
	void			*it;
	float			l_dist;
}	t_utils;

static void	init_utils(t_utils *u, t_ray3 *r)
{
	u->hit = false;
	u->l_dist = vector3_length(r->direction);
	r->direction = vector3_scm(r->direction, 1 / u->l_dist);
}

static float	adj(bool *is_hit, t_hit_record *tmp,
								t_hit_record *rec, t_color3 *color)
{
	*is_hit = true;
	tmp->c = *color;
	*rec = *tmp;
	return (tmp->t);
}

bool	hit_objects(const t_ray3 *r, const t_objects *obj,
					t_hit_record *rec, t_range rng)
{
	t_utils			u;

	u.hit = false;
	u.it = obj->sphere;
	while (u.it)
	{
		if (hit_sphere(r, u.it, &u.rec, rng))
			rng.t_max = adj(&u.hit, &u.rec, rec, &((t_sphere *) u.it)->color);
		u.it = ((t_sphere *) u.it)->next;
	}
	u.it = obj->plane;
	while (u.it)
	{
		if (hit_plane(r, u.it, &u.rec, rng))
			rng.t_max = adj(&u.hit, &u.rec, rec, &((t_plane *) u.it)->color);
		u.it = ((t_plane *) u.it)->next;
	}
	u.it = obj->cylinder;
	while (u.it)
	{
		if (hit_cylinder(r, u.it, &u.rec, rng))
			rng.t_max = adj(&u.hit, &u.rec, rec, &((t_cylinder *) u.it)->color);
		u.it = ((t_cylinder *) u.it)->next;
	}
	return (u.hit);
}

bool	hit_any(t_ray3 r, const t_objects *obj, const t_range rng)
{
	t_utils			u;

	init_utils(&u, &r);
	u.it = obj->sphere;
	while (u.it && !u.hit)
	{
		if (hit_sphere(&r, u.it, &u.rec, rng) && u.rec.t < u.l_dist)
			u.hit = true;
		u.it = ((t_sphere *) u.it)->next;
	}
	u.it = obj->plane;
	while (u.it && !u.hit)
	{
		if (hit_plane(&r, u.it, &u.rec, rng) && u.rec.t < u.l_dist)
			u.hit = true;
		u.it = ((t_plane *) u.it)->next;
	}
	u.it = obj->cylinder;
	while (u.it && !u.hit)
	{
		if (hit_cylinder(&r, u.it, &u.rec, rng) && u.rec.t < u.l_dist)
			u.hit = true;
		u.it = ((t_cylinder *) u.it)->next;
	}
	return (u.hit);
}

void	destroy_objects(t_objects *objs)
{
	void	*it;
	void	*pivot;

	it = objs->sphere;
	while (it)
	{
		pivot = it;
		it = ((t_sphere *) it)->next;
		free(pivot);
	}
	it = objs->plane;
	while (it)
	{
		pivot = it;
		it = ((t_plane *) it)->next;
		free(pivot);
	}
	it = objs->cylinder;
	while (it)
	{
		pivot = it;
		it = ((t_cylinder *) it)->next;
		free(pivot);
	}
}
