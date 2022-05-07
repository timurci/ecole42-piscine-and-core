#include "fractol.h"



void	circle(t_mlx *app, t_img *img)
{
	t_vector	v;

	vector_init(&v);
	while (v.pos_y < app->size_y)
	{
		v.pos_x = 0;
		while (v.pos_x < app->size_x)
		{
		}
		v.pos_y++;
	}
}
