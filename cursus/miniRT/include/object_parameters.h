#ifndef OBJECT_PARAMETERS_H
# define OBJECT_PARAMETERS_H

# include "point3.h"
# include "vector3.h"

typedef struct s_record
{
	t_point3	p;
	t_vec3		n;
	float		t;
}	t_hit_record;

typedef struct s_range
{
	float	t_min;
	float	t_max;
}	t_range;

t_range	set_range(const float min, const float max);

#endif
