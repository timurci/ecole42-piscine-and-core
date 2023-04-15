/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:51:17 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 14:01:24 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include <stdlib.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

//create a vec3 struct at stack
t_vec3	vector3_set(const float x, const float y, const float z);
//create a copy of v at heap
t_vec3	*copy_vector3(const t_vec3 v);

//element-wise addition
t_vec3	vector3_add(const t_vec3 v1, const t_vec3 v2);
//scalar multiplication of vector
t_vec3	vector3_scm(const t_vec3 v, const float t);
//element-wise multiplication
t_vec3	vector3_ewm(const t_vec3 v1, const t_vec3 v2);

#endif
