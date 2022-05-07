#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> //remove later
# include <math.h>

typedef struct	s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		s_line;
	int		end;
}				t_img;

typedef	struct	s_mlx
{
	void	*mlx;
	void	*win;
	char	*title;
	int		**colors;
	t_img	*frame;
	char	is_modified;
	char	mode;
	int		size_x;
	int		size_y;
	int		mouse_x;
	int		mouse_y;
	int		border;
	int		offset_x;
	int		offset_y;
}				t_mlx;

char	*ft_strdup(char *str);
int		sign(int n);

void	set_mlx(t_mlx *app);
int		destroy_win(void *param);
int		put_frame(void *param);
int		activate_frame(void *param);

int		zoom_handler(t_mlx *app, int button, int x, int y);
int		key_handler(int keycode, void *param);
int		mouse_handler(int button, int x, int y, void *param);

void	fill_bits(t_img *img, int x, int y, int color);
void	paint_bg(t_img *img, t_mlx *app, int color);
void	call_item(t_mlx *app, char (*f)(t_mlx *, int, int), char mode);
void	draw_item(t_mlx *app, char (*f)(t_mlx *, int, int), int *colors);

char	in_circle(t_mlx *app, int x, int y);
char	in_mandelbrot(t_mlx *app, int x, int y);
void	mandelbrot(float *real, float *imgry, float dx, float dy);


#endif
