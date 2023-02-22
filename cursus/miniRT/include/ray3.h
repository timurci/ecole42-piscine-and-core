#ifndef RAY3_H
# define RAY3_H

# include "vector3.h"
# include "point3.h"

typedef struct s_ray3
{
	t_point3	origin;
	t_vec3		direction;
} t_ray3;

t_ray3		ray3_set(t_point3 origin, t_vec3 direction);
t_ray3		*copy_ray3(const t_ray3 r);

t_point3	ray3_pos(const t_ray3 r, const float t);

#endif
