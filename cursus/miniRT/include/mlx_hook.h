#ifndef MLX_HOOK
# define MLX_HOOK

# include "keycodes.h"

# include <stdio.h>
# include "mlx.h"
# include "mlx_core.h"
# include "mlx_utils.h"

int	terminate(void *core);
int	t_mlx_loop_hook(void *core);
int	t_mlx_key_hook(int keycode, void *core);

#endif
