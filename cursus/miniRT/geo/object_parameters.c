#include "object_parameters.h"

t_range	set_range(const float min, const float max)
{
	t_range	x;

	x.t_min = min;
	x.t_max = max;
	return (x);
}
