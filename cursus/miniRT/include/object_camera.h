#ifndef OBJECT_CAMERA_H
# define OBJECT_CAMERA_H

# include "point3.h"
# include "vector3.h"
# include "ray3.h"

typedef struct s_camera
{
	float	aspect_ratio;
	float	vp_width;
	float	vp_height;
	float	focal_length;
	t_point3	origin;
	t_point3	lower_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
}	t_camera;

t_camera	camera_set(const float aspect_ratio, const float vp_height,
			const float focal_length, const t_point3 origin);
t_ray3		get_ray(const t_camera cam, const float u, const float v);

#endif
