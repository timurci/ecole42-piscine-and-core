/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:51:17 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_SPHERE_H
# define OBJECT_SPHERE_H

# include "ray3.h"
# include "point3.h"
# include "vector3.h"
# include "vector3_utils.h"
# include "color3.h"
# include "stdlib.h"
# include "object_parameters.h"
# include <stdbool.h>

typedef struct s_sphere
{
	t_point3		center;
	t_color3		color;
	float			radius;
	struct s_sphere	*next;
}	t_sphere;

//t_sphere	set_sphere(const t_point3 center, const float radius,
//				const t_point3 color);
t_sphere	*add_sphere(t_sphere *list, const t_point3 center,
				const float rad, const t_color3 color);
bool		hit_sphere(const t_ray3 *r, const t_sphere *obj,
				t_hit_record *rec, const t_range range);

#endif
