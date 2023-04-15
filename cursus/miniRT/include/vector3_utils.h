/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 14:01:57 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_UTILS_H
# define VECTOR3_UTILS_H

# include "vector3.h"
# include <math.h>

t_vec3	vector3_crp(const t_vec3 v1, const t_vec3 v2); //cross product
float	vector3_dtp(const t_vec3 v1, const t_vec3 v2); //dot product

float	vector3_length(const t_vec3 v);
float	vector3_length_squared(const t_vec3 v);

//returns unit vector of v // v/v.length();
t_vec3	vector3_unit(const t_vec3 v);

#endif
