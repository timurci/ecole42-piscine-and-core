#include "object_camera.h"

t_camera	camera_set(const float aspect_ratio, const float vp_height,
			const float focal_length, const t_point3 origin)
{
	t_camera	cam;

	cam.aspect_ratio = aspect_ratio;
	cam.vp_height = vp_height;
	cam.vp_width = aspect_ratio * vp_height;
	cam.focal_length = focal_length;
	cam.origin = origin;
	cam.horizontal = vector3_set(cam.vp_width, 0.0f, 0.0f);
	cam.vertical = vector3_set(0.0f, cam.vp_height, 0.0f);
	cam.lower_left_corner = vector3_add(cam.origin,
			vector3_add(vector3_scm(cam.horizontal, -0.5f),
				vector3_add(vector3_scm(cam.vertical, -0.5f),
					vector3_set(0, 0, -cam.focal_length))
				)
			);
	return (cam);
}

t_ray3	get_ray(const t_camera cam, const float u, const float v)
{
	t_ray3	r;

	r = ray3_set(cam.origin,
			vector3_add(cam.lower_left_corner,
				vector3_add(vector3_scm(cam.horizontal, u),
					vector3_add(vector3_scm(cam.vertical, v),
						vector3_scm(cam.origin, -1))
					)
				)
			);
	return (r);
}
