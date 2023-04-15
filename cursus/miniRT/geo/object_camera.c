#include "object_camera.h"

t_camera	camera_set(const float aspect_ratio, const float vfov,
			const t_vec3 normal, const t_point3 origin)
{
	t_camera		cam;
	const float 	focal_length = 1.0f;
	const float		v_dist_2 = focal_length * tan((float) vfov * M_PI_2 / 180.0f);
	const t_vec3	w = vector3_unit(vector3_scm(normal, -1));
	const t_vec3	u = vector3_unit(vector3_crp(vector3_set(0, 1, 0), w));
	const t_vec3	v = vector3_crp(w, u);

	cam.aspect_ratio = aspect_ratio;
	cam.vp_width = 2.0f * v_dist_2;
	cam.vp_height = cam.vp_width / aspect_ratio;
	cam.focal_length = focal_length;
	cam.origin = origin;
	cam.horizontal = vector3_scm(u, cam.vp_width);
	cam.vertical = vector3_scm(v, cam.vp_height);
	cam.lower_left_corner = vector3_add(cam.origin,
			vector3_add(vector3_scm(cam.horizontal, -0.5f),
				vector3_add(vector3_scm(cam.vertical, -0.5f),
					vector3_scm(w, -1))
				)
			);
	return (cam);
}

t_ray3	get_ray(const t_camera *cam, const float *u, const float *v)
{
	t_ray3	r;

	r = ray3_set(cam->origin,
			vector3_add(cam->lower_left_corner,
				vector3_add(vector3_scm(cam->horizontal, *u),
					vector3_add(vector3_scm(cam->vertical, *v),
						vector3_scm(cam->origin, -1))
					)
				)
			);
	return (r);
}
