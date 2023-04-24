/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder_params.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:47:25 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/24 09:47:56 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_cylinder.h"

t_cylinder_params	cylinder_params(const float radius, const float height,
						const t_vec3 axis)
{
	t_cylinder_params	params;

	params.radius = radius;
	params.height = height;
	params.axis = axis;
	return (params);
}
