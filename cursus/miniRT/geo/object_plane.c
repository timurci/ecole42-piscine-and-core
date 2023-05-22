/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:40 by tcakmako          #+#    #+#             */
/*   Updated: 2023/05/22 17:55:58 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_plane.h"

t_plane	*add_plane(t_plane *list, const t_point3 ref,
				const t_vec3 normal, const t_color3 color)
{
	t_plane	*obj;
	t_plane	*itr;

	obj = malloc(sizeof(*obj));
	obj->ref = vector3_scm(ref, -1);
	obj->normal = normal;
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

bool	hit_plane(const t_ray3 *r, const t_plane *obj,
					t_hit_record *rec, const t_range range)
{
	const t_vec3	or = vector3_add(r->origin, obj->ref);
	const float		on = vector3_dtp(obj->normal, or);
	const float		dn = vector3_dtp(obj->normal, r->direction);
	const float		root = -on / dn;

	if (root < range.t_min || root > range.t_max)
		return (false);
	rec->t = root;
	rec->p = ray3_tpos(r, root);
	if (on < 0)
		rec->n = vector3_scm(obj->normal, -1);
	else
		rec->n = obj->normal;
	return (true);
}
