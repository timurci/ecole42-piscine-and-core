/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/05/22 22:54:51 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "ray3.h"
# include "vector3.h"
# include "point3.h"

# include "object_parameters.h"
# include "object_sphere.h"
# include "object_plane.h"
# include "object_camera.h"
# include "object_light.h"
# include "object_cylinder.h"

# include <stdbool.h>

typedef struct s_objects
{
	t_sphere		*sphere;
	t_cylinder		*cylinder;
	t_plane			*plane;
	t_hit_record	record;
	t_camera		camera;
	t_light_p		point_light;
	t_light_a		ambient_light;
}	t_objects;

bool	hit_objects(const t_ray3 *r, const t_objects *obj,
			t_hit_record *rec, const t_range range);

bool	hit_any(t_ray3 r, const t_objects *obj, const t_range range);

void	destroy_objects(t_objects *objs);

#endif
