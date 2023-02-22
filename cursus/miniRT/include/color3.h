#ifndef COLOR3_H
# define COLOR3_H

# include "vector3.h"

typedef t_vec3 t_color3;

//scaled rgb values [0,1]
t_color3	color3_set(const float r, const float g, const float b);
//returns 255.999 * {r,g,b}
int			color3_get_color(const t_color3 c);

#endif
