#include "ray3.h"

t_ray3	ray3_set(t_point3 origin, t_vec3 direction)
{
	t_ray3	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_ray3	*copy_ray3(const t_ray3 r)
{
	t_ray3	*p;

	p = malloc(sizeof(*p));
	*p = r;
	return (p);
}

t_point3	ray3_tpos(const t_ray3 r, const float t)
{
	return (vector3_add(r.origin, vector3_scm(r.direction, t)));
}
