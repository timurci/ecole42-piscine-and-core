#include "object_sphere.h"
#include "objects.h"

bool	hit_objects(const t_ray3 r, t_objects obj,
					t_hit_record *rec, const t_range rng)
{
	t_hit_record	tmp;
	bool			is_hit;
	float			closest;

	is_hit = false;
	closest = rng.t_max;
	while (obj.sphere)
	{
		if (hit_sphere(r, *obj.sphere, &tmp, set_range(rng.t_min, closest)))
		{
			is_hit = true;
			closest = tmp.t;
			*rec = tmp;
		}
		obj.sphere = obj.sphere->next;
	}
	return (is_hit);
}

void	destroy_objects(t_objects *objs)
{
	t_sphere	*scan;
	void		*pivot;

	scan = objs->sphere;
	while (scan)
	{
		pivot = scan;
		scan = scan->next;
		free(pivot);
	}
}
