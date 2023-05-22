#ifndef PARSE_H
# define PARSE_H

# include "vector3.h"
# include "vector3_utils.h"
# include "vector3_utils_extended.h"
# include "color3.h"
# include "point3.h"
# include "ray3.h"

# include "objects.h"
# include "object_parameters.h"
# include "object_light.h"
# include "object_camera.h"
# include "object_sphere.h"
# include "object_plane.h"
# include "object_cylinder.h"

# include "get_next_line.h"

t_objects	*parse(const char *filename, const float aspect_ratio);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *str);

#endif
