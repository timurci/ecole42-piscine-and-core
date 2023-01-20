#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "mlx_core.h"
#include "mlx_utils.h"
#include "mlx_hook.h"

void	fill_bg(t_mlx_image *img, int color)
{
	for (int i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->width; j++)
		{
			t_mlx_image_set_pixel(img, j, i, color);
		}
	}
}

int	main(void)
{
	t_mlx_core	*mlx_core;

	mlx_core = t_mlx_init_core(800, 600, "Test Application");
	mlx_loop_hook(mlx_core->ptr, t_mlx_loop_hook, mlx_core);
	mlx_key_hook(mlx_core->win, t_mlx_key_hook, mlx_core);
	mlx_hook(mlx_core->win, 17, 0, terminate, mlx_core);

	//test
	fill_bg(mlx_core->frame[0], 0x00FF0000);
	fill_bg(mlx_core->frame[1], 0x0000FF00);
	//test
	
	mlx_loop(mlx_core->ptr);
	t_mlx_destroy_core(mlx_core);
	return (0);
}
