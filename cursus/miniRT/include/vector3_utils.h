#ifndef VECTOR3_UTILS_H
# define VECTOR3_UTILS_H

# include "vector3.h"
# include <math.h>

t_vec3	vector3_crp(const t_vec3 v1, const t_vec3 v2); //cross product
float	vector3_dtp(const t_vec3 v1, const t_vec3 v2); //dot product

float	vector3_length(const t_vec3 v);
float	vector3_length_squared(const t_vec3 v);

t_vec3	vector3_unit(const t_vec3 v); //returns unit vector of v // v/v.length();

#endif
