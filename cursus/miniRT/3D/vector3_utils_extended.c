/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_utils_extended.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:52:47 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 16:03:30 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3_utils_extended.h"

t_vec3	vector3_random(void)
{
	const float	x = rand42() / (RAND_MAX + 1.0f);
	const float	y = rand42() / (RAND_MAX + 1.0f);
	const float	z = rand42() / (RAND_MAX + 1.0f);
	t_vec3		vector;

	vector = vector3_set(x, y, z);
	if (vector3_length_squared(vector) > 1.0f)
		return (vector3_random());
	return (vector3_set(x, y, z));
}

t_vec3	vector3_random_minmax(const float min, const float max)
{
	t_vec3	vector;

	vector = vector3_scm(vector3_random(), max - min);
	vector.x += min;
	vector.y += min;
	vector.z += min;
	return (vector);
}
