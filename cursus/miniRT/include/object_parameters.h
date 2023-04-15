/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parameters.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:51:17 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_PARAMETERS_H
# define OBJECT_PARAMETERS_H

# include "point3.h"
# include "vector3.h"
# include "color3.h"

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		n;
	t_color3	c;
	float		t;
}	t_hit_record;

typedef struct s_range
{
	float	t_min;
	float	t_max;
}	t_range;

t_range	set_range(const float min, const float max);

#endif
