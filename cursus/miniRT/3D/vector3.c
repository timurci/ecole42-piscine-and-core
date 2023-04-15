/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:52:47 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:52:47 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	vector3_set(const float x, const float y, const float z)
{
	t_vec3	n_v;

	n_v.x = x;
	n_v.y = y;
	n_v.z = z;
	return (n_v);
}

t_vec3	*copy_vector3(const t_vec3 v)
{
	t_vec3	*p;

	p = malloc(sizeof(*p));
	*p = v;
	return (p);
}

t_vec3	vector3_add(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	n_v;

	n_v = v1;
	n_v.x += v2.x;
	n_v.y += v2.y;
	n_v.z += v2.z;
	return (n_v);
}

t_vec3	vector3_scm(const t_vec3 v, const float t)
{
	t_vec3	n_v;

	n_v = v;
	n_v.x *= t;
	n_v.y *= t;
	n_v.z *= t;
	return (n_v);
}

t_vec3	vector3_ewm(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	n_v;

	n_v = v1;
	n_v.x *= v2.x;
	n_v.y *= v2.y;
	n_v.z *= v2.z;
	return (n_v);
}
