#ifndef MLX_CORE_H
# define MLX_CORE_H

# include "mlx.h"
# include <stdlib.h>

typedef struct s_mlx_image
{
	void	*ptr;
	char	*data;
	int		width;
	int		height;
	int		bbp;
	int		size_line;
	int		endian;
} t_mlx_image;

typedef struct s_mlx_core
{
	void		*ptr;
	void		*win;
	int			width;
	int			height;
	t_mlx_image	*frame[2];
	int			frame_repeat;
} t_mlx_core;

//init
t_mlx_core	*t_mlx_init_core(int size_x, int size_y, char *title);
t_mlx_image	*t_mlx_init_image(t_mlx_core *core, int size_x, int size_y);

//destroy
void		t_mlx_destroy_core(t_mlx_core *core);

//misc
void		t_mlx_core_switch_frame(t_mlx_core *core);

#endif
