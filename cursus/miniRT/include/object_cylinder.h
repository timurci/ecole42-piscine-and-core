/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/18 00:36:38 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_CYLINDER_H
# define OBJECT_CYLINDER_H

# include "ray3.h"
# include "point3.h"
# include "vector3.h"
# include "vector3_utils.h"
# include "color3.h"
# include "stdlib.h"
# include "object_parameters.h"
# include <stdbool.h>

typedef struct s_cylinder
{
	t_vec3				axis;
	t_point3			center;
	t_point3			center_t;
	t_point3			n_center_t;
	t_point3			center_b;
	t_point3			n_center_b;
	t_color3			color;
	float				radius;
	float				radius2;
	float				height;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_cylinder_params
{
	float		radius;
	float		height;
	t_vec3		axis;
}	t_cylinder_params;

t_cylinder			*add_cylinder(t_cylinder *list, const t_point3 center,
						const t_cylinder_params params, const t_color3 color);
bool				hit_cylinder(const t_ray3 *r, const t_cylinder *obj,
						t_hit_record *rec, const t_range range);

t_cylinder_params	cylinder_params(const float radius, const float height,
						const t_vec3 axis);

#endif
