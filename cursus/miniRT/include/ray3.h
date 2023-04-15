/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 14:02:42 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY3_H
# define RAY3_H

# include "vector3.h"
# include "point3.h"

typedef struct s_ray3
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray3;

t_ray3		ray3_set(t_point3 origin, t_vec3 direction);
t_ray3		*copy_ray3(const t_ray3 r);
void		ray3ppp_set(t_ray3 *ray_p, const t_point3 *origin,
				const t_vec3 *direction);

t_point3	ray3_tpos(const t_ray3 *r, const float t);

#endif
