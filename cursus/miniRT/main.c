#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

# define SIZE_X 800
# define SIZE_Y 600
# define TITLE "My awesome application!"

typedef struct s_mlx_image
{
	void	*ptr;
	char	*data;
	int		bbp;
	int		size_line;
	int		endian;
} t_mlx_image;

//x0 y0 top left corner
void	put_pixel(t_mlx_image *img, int x, int y, int color)
{
	unsigned int *dst; 
	
	dst = (unsigned int *) &img->data[y * img->size_line + (x * img->bbp/8)];
	*dst = color;
}

void	put_square(t_mlx_image *img, int *xy, int size, int color)
{
	for (int i = xy[0]; i < xy[0] + size; i++)
	{
		for (int j = xy[1]; j < xy[1] + size; j++)
		{
			put_pixel(img, i, j, color);
		}
	}
}

int	main(void)
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_mlx_image	frame[2];

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	mlx_win = mlx_new_window(mlx_ptr, SIZE_X, SIZE_Y, TITLE);
	frame[0].ptr = mlx_new_image(mlx_ptr, SIZE_X, SIZE_Y);
	frame[0].data = mlx_get_data_addr(frame[0].ptr, &frame[0].bbp,
			&frame[0].size_line, &frame[0].endian);
	int xy[] = {50, 50};
	put_square(&frame[0], xy, 100, 0x00ff0a00);
	mlx_put_image_to_window(mlx_ptr, mlx_win, frame[0].ptr, 0,0);
	mlx_put_image_to_window(mlx_ptr, mlx_win, frame[0].ptr, 150, 200);
	mlx_loop(mlx_ptr);
	while (1)
		;
	return (0);
}
