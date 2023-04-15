/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:40 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:51:40 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_sphere.h"

typedef struct s_sphere_solver
{
	t_vec3	oc;
	float	a;
	float	half_b;
	float	c;
	float	discriminant;
}	t_sphere_solver;

t_sphere	*add_sphere(t_sphere *list, const t_point3 center,
				const float rad, const t_point3 color)
{
	t_sphere	*obj;
	t_sphere	*itr;

	obj = malloc(sizeof(*obj));
	obj->center = center;
	obj->radius = rad;
	obj->color = color;
	obj->next = NULL;
	if (!list)
		return (obj);
	itr = list;
	while (itr->next)
		itr = itr->next;
	itr->next = obj;
	return (list);
}

static t_sphere_solver	solve_quadratic_equation(const t_ray3 *r,
						const t_point3 *center, const float *radius)
{
	t_sphere_solver	ss;

	ss.oc = vector3_add(r->origin, vector3_scm(*center, -1));
	ss.a = vector3_dtp(r->direction, r->direction);
	ss.half_b = vector3_dtp(ss.oc, r->direction);
	ss.c = vector3_dtp(ss.oc, ss.oc) - *radius * *radius;
	ss.discriminant = ss.half_b * ss.half_b - ss.a * ss.c;
	return (ss);
}

bool	hit_sphere(const t_ray3 *r, const t_sphere *obj,
					t_hit_record *rec, const t_range range)
{
	const t_sphere_solver	ss = solve_quadratic_equation(r, &obj->center,
			&obj->radius);
	float					sqrtd;
	float					root;

	if (ss.discriminant < 0)
		return (false);
	sqrtd = sqrt(ss.discriminant);
	root = (-ss.half_b - sqrtd) / ss.a;
	if (root < range.t_min || range.t_max < root)
	{
		root = (-ss.half_b + sqrtd) / ss.a;
		if (root < range.t_min || range.t_max < root)
			return (false);
	}
	rec->t = root;
	rec->p = ray3_tpos(r, root);
	rec->n = vector3_scm(vector3_add(rec->p, vector3_scm(obj->center, -1)),
			1 / obj->radius);
	return (true);
}
