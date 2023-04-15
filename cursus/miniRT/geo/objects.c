#include "object_sphere.h"
#include "objects.h"

static float	adjust(bool *is_hit, t_hit_record *tmp,
								t_hit_record *rec, t_color3 *color)
{
	*is_hit = true;
	tmp->c = *color;
	*rec = *tmp;
	return (tmp->t);
}

bool	hit_objects(const t_ray3 *r, const t_objects *obj,
					t_hit_record *rec, const t_range rng)
{
	t_hit_record	tmp;
	bool			is_hit;
	float			closest;
	void			*scan;

	is_hit = false;
	closest = rng.t_max;
	scan = obj->sphere;
	while (scan)
	{
		if (hit_sphere(r, scan, &tmp, set_range(rng.t_min, closest)))
			closest = adjust(&is_hit, &tmp, rec, &((t_sphere *) scan)->color);
		//if (hit_sphere(r, scan, &tmp, set_range(rng.t_min, closest)))
		//{
		//	is_hit = true;
		//	closest = tmp.t;
		//	tmp.c = ((t_sphere *) scan)->color;
		//	*rec = tmp;
		//}
		scan = ((t_sphere *) scan)->next;
	}
	scan = obj->plane;
	while (scan)
	{
		if (hit_plane(r, scan, &tmp, set_range(rng.t_min, closest)))
			closest = adjust(&is_hit, &tmp, rec, &((t_plane *) scan)->color);
		scan = ((t_plane *) scan)->next;
	}
	return (is_hit);
}

bool	hit_any(const t_ray3 r, const t_objects *obj, const t_range rng)
{
	bool			is_hit;
	t_sphere		*sphere_scan;
	t_hit_record	tmp;

	is_hit = false;
	sphere_scan = obj->sphere;
	while (sphere_scan && !is_hit)
	{
		if (hit_sphere(&r, sphere_scan, &tmp, set_range(rng.t_min, rng.t_max)))
			is_hit = true;
		sphere_scan = sphere_scan->next;
	}
	return (is_hit);
}

void	destroy_objects(t_objects *objs)
{
	void	*scan;
	void		*pivot;

	scan = objs->sphere;
	while (scan)
	{
		pivot = scan;
		scan = ((t_sphere *) scan)->next;
		free(pivot);
	}
	scan = objs->plane;
	while (scan)
	{
		pivot = scan;
		scan = ((t_plane *) scan)->next;
		free(pivot);
	}
}
