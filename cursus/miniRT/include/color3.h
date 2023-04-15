#ifndef COLOR3_H
# define COLOR3_H

# include "vector3.h"
# include <math.h>

typedef t_vec3 t_color3;

//scaled rgb values [0,1]
t_color3	color3_set(const float r, const float g, const float b);
t_color3	color3_add(const t_color3 c1, const t_color3 c2);

void		color3p_set(t_color3 *c, const float r,
						const float g, const float b);

void		color3_gamma2(t_color3 *c);

//returns 255.999 * {r,g,b}
int			color3_get_color(const t_color3 c);

#endif
