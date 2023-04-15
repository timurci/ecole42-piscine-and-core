#include "vector3_utils_extended.h"

t_vec3	vector3_random(void)
{
	const float	x = rand() / (RAND_MAX + 1.0f);
	const float	y = rand() / (RAND_MAX + 1.0f);
	const float	z = rand() / (RAND_MAX + 1.0f);
	t_vec3		vector = vector3_set(x, y, z);

	if (vector3_length_squared(vector) > 1.0f)
		return (vector3_random());
	return (vector3_set(x, y, z));
}

t_vec3	vector3_random_minmax(const float min, const float max)
{
	t_vec3	vector;

	vector = vector3_scm(vector3_random(), max - min);
	vector.x += min;
	vector.y += min;
	vector.z += min;
	return (vector);
}
