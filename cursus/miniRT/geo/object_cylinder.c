/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:40 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/24 09:50:44 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_cylinder.h"

//delete
#include <stdio.h>

typedef struct s_cylinder_solver
{
	t_vec3				oc;
	t_vec3				oc_t;
	float				a;
	float				half_b;
	float				c;
	float				discriminant;
	float				oc_dot_axis;
	float				oc_t_dot_axis;
	float				oc_dot_dir;
	float				oc_t_dot_dir;
	float				dir_dot_axis;
	float				oc2;
	float				oc2_t;
	float				dir2;
	const t_range		*rng;
}	t_cylinder_solver;

t_cylinder	*add_cylinder(t_cylinder *list, const t_point3 center,
				const t_cylinder_params params, const t_point3 color)
{
	t_cylinder	*obj;
	t_cylinder	*itr;
	t_vec3		tmp;

	obj = malloc(sizeof(*obj));
	obj->center = center;
	obj->axis = vector3_unit(params.axis);
	obj->radius = params.radius;
	obj->radius2 = params.radius * params.radius;
	obj->height = params.height;
	tmp = vector3_scm(obj->axis, -obj->height / 2);
	obj->center_b = vector3_add(center, tmp);
	obj->n_center_b = vector3_scm(obj->center_b, -1);
	tmp = vector3_scm(obj->axis, obj->height / 2);
	obj->center_t = vector3_add(center, tmp);
	obj->n_center_t = vector3_scm(obj->center_t, -1);
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

static t_cylinder_solver	solve_quadratic_equation(const t_ray3 *r,
				const t_cylinder *obj, const t_range *rng)
{
	t_cylinder_solver	cs;

	cs.oc = vector3_add(r->origin, obj->n_center_b);
	cs.oc_t = vector3_add(r->origin, obj->n_center_t);
	cs.oc2 = vector3_dtp(cs.oc, cs.oc);
	cs.oc2_t = vector3_dtp(cs.oc_t, cs.oc_t);
	cs.dir2 = vector3_dtp(r->direction, r->direction);
	cs.oc_dot_axis = vector3_dtp(cs.oc, obj->axis);
	cs.oc_t_dot_axis = vector3_dtp(cs.oc_t, obj->axis);
	cs.oc_dot_dir = vector3_dtp(cs.oc, r->direction);
	cs.oc_t_dot_dir = vector3_dtp(cs.oc_t, r->direction);
	cs.dir_dot_axis = vector3_dtp(r->direction, obj->axis);
	cs.a = cs.dir2;
	cs.a -= cs.dir_dot_axis * cs.dir_dot_axis;
	cs.half_b = cs.oc_dot_dir;
	cs.half_b -= cs.oc_dot_axis * cs.dir_dot_axis;
	cs.c = cs.oc2 - obj->radius2;
	cs.c -= cs.oc_dot_axis * cs.oc_dot_axis;
	cs.discriminant = cs.half_b * cs.half_b - cs.a * cs.c;
	cs.rng = rng;
	return (cs);
}

static float	get_alpha(const t_cylinder_solver *cs, const float *root)
{
	return (*root * cs->dir_dot_axis + cs->oc_dot_axis);
}

// Optimized hit_plane function to find intersection with cylinder caps.
bool	hit_caps(const t_ray3 *r, const t_cylinder *obj, t_hit_record *rec,
			const t_cylinder_solver *cs)
{
	const float	root_t = -cs->oc_t_dot_axis / cs->dir_dot_axis;
	const float	root_b = -cs->oc_dot_axis / cs->dir_dot_axis;
	float		root;
	float		length;

	if (root_t < root_b)
		root = root_t;
	else
		root = root_b;
	length = root * root * cs->dir2;
	if (root == root_t)
		length += (root + root) * cs->oc_t_dot_dir + cs->oc2_t;
	else
		length += (root + root) * cs->oc_dot_dir + cs->oc2;
	if (length > obj->radius2)
		return (false);
	if (root < cs->rng->t_min || root > cs->rng->t_max)
		return (false);
	rec->t = root;
	rec->p = ray3_tpos(r, root);
	rec->n = obj->axis;
	if (root == root_b)
		rec->n = vector3_scm(obj->axis, -1);
	return (true);
}

bool	hit_cylinder(const t_ray3 *r, const t_cylinder *obj,
					t_hit_record *rec, const t_range range)
{
	const t_cylinder_solver	cs = solve_quadratic_equation(r, obj, &range);
	float					sqrtd;
	float					root;
	float					alpha;

	if (hit_caps(r, obj, rec, &cs))
		return (true);
	if (cs.discriminant < 0)
		return (false);
	sqrtd = sqrt(cs.discriminant);
	root = (-cs.half_b - sqrtd) / cs.a;
	if (root < range.t_min || range.t_max < root)
	{
		root = (-cs.half_b + sqrtd) / cs.a;
		if (root < range.t_min || range.t_max < root)
			return (false);
	}
	alpha = get_alpha(&cs, &root);
	if (alpha < 0 || alpha > obj->height)
		return (false);
	rec->t = root;
	rec->p = ray3_tpos(r, root);
	rec->n = vector3_add(vector3_add(rec->p, obj->n_center_b),
			vector3_scm(obj->axis, -alpha));
	return (true);
}
