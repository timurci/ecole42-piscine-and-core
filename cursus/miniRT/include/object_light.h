#ifndef OBJECT_LIGHT
# define OBJECT_LIGHT

# include "point3.h"
# include "color3.h"
# include "ray3.h"
# include "vector3_utils.h"
# include "object_parameters.h"

typedef struct s_light_p
{
	t_point3	p;
	t_color3	c;
	//float		i;
}	t_light_p;

typedef struct s_light_a
{
	t_color3	c;
	//float		i;
}	t_light_a;

t_light_p	set_point_light(const t_color3 c, const float i, const t_point3 p);
t_light_a	set_ambient_light(const t_color3 c, const float i);

t_ray3		point_to_light(const t_light_p *l, const t_point3 *p);

// r.n * unit(l.p - r.p)
float		point_light_factor(const t_light_p *l, const t_hit_record *r);

#endif
