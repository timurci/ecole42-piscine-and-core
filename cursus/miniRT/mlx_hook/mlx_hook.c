#include "mlx_hook.h"

int	terminate(void *core)
{
	t_mlx_destroy_core(core);
	exit(EXIT_SUCCESS);
	return (0);
}

int	t_mlx_loop_hook(void *param)
{
	t_mlx_core	*core;

	core = param;
	if (core->frame_repeat)
	{
		mlx_put_image_to_window(core->ptr, core->win,
				core->frame[1]->ptr, 0, 0);
		--core->frame_repeat;
	}
	return (0);
}

int	t_mlx_key_hook(int keycode, void *core)
{
	if (keycode == KEY_1)
	{
		t_mlx_core_switch_frame(core);
		printf("Frame switched\n");
	}
	else if (keycode == KEY_ESC)
		terminate(core);
	return (0);
}
