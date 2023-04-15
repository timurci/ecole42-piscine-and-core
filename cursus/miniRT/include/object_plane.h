/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:51:17 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_PLANE_H
# define OBJECT_PLANE_H

# include "ray3.h"
# include "point3.h"
# include "vector3.h"
# include "vector3_utils.h"
# include "color3.h"
# include "stdlib.h"
# include "object_parameters.h"
# include <stdbool.h>

typedef struct s_plane
{
	t_point3		ref;
	t_vec3			normal;
	t_color3		color;
	struct s_plane	*next;
}	t_plane;

//t_plane	set_plane(const t_point3 ref, const t_vec3 normal);
t_plane	*add_plane(t_plane *list, const t_point3 ref,
			const t_vec3 normal, const t_color3 color);
bool	hit_plane(const t_ray3 *r, const t_plane *obj,
			t_hit_record *rec, const t_range range);

#endif
