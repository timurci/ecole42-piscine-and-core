#ifndef PARSE_H
# define PARSE_H

#include "vector3.h"
#include "vector3_utils.h"
#include "vector3_utils_extended.h"
#include "ray3.h"
#include "color3.h"
#include "point3.h"

#include "objects.h"
#include "object_parameters.h"
#include "object_sphere.h"
#include "object_camera.h"
#include "object_light.h"

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_compulsory
{
    bool    C;
    bool    A;
    bool    L;
}	t_compulsory;

char		**ft_split(char const *s, char c);
t_objects	*parse(const char *filename, const float aspect_ratio);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *str);

#endif
