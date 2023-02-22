#include "vector3.h"
#include "color3.h"

t_color3	color3_set(const float r, const float g, const float b)
{
	return (vector3_set(r, g, b));
}

int	color3_get_color(const t_color3 c)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = 255.999 * c.x;
	g = 255.999 * c.y;
	b = 255.999 * c.z;
	return ((r << 16) | (g << 8) | b);
}
