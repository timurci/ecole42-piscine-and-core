/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:52:47 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:56:08 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "vector3_utils.h"

t_vec3	vector3_crp(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	n_v;

	n_v.x = v1.y * v2.z - v1.z * v2.y;
	n_v.y = v1.z * v2.x - v1.x * v2.z;
	n_v.z = v1.x * v2.y - v1.y * v2.x;
	return (n_v);
}

float	vector3_dtp(const t_vec3 v1, const t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	vector3_length(const t_vec3 v)
{
	return (sqrt(vector3_length_squared(v)));
}

float	vector3_length_squared(const t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vector3_unit(const t_vec3 v)
{
	return (vector3_scm(v, 1 / vector3_length(v)));
}
