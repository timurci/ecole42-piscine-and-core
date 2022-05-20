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

typedef struct	s_colors
{
	int				bg;
	int				fg;
	struct s_colors	*next;
}				t_colors;

typedef	struct	s_mlx
{
	void			*mlx;
	void			*win;
	char			*title;
	t_colors		*colors;
	t_img			*frame;
	char			is_modified;
	char			mode;
	int				size_x;
	int				size_y;
	int				center_x;
	int				center_y;
	int				mouse_x;
	int				mouse_y;
	size_t			border;
	int				max_iter;
	int				offset_x;
	int				offset_y;
}				t_mlx;

void		ft_bzero(void *s, size_t n);
char		*ft_strdup(char *str);
int			sign(int n);

void		set_mlx(t_mlx *app);
int			destroy_win(void *param);
int			put_frame(void *param);
int			activate_frame(void *param);
t_colors	*init_color_palette(void);

int			zoom_handler(t_mlx *app, int button, int x, int y);
int			key_handler(int keycode, void *param);
int			mouse_handler(int button, int x, int y, void *param);

void		change_itr(t_mlx *app, int keycode);
void		shift_item(t_mlx *app, int keycode);

void		fill_bits(t_img *img, int x, int y, int color);
void		fill_other_half(t_mlx *app, t_img *img);
void		paint_bg(t_img *img, t_mlx *app, int color);
void		call_item(t_mlx *app, void (*f)(t_mlx *, t_img *), char mode);
void		draw_item(t_mlx *app, void (*f)(t_mlx *, t_img *));
void		redraw(t_mlx *app);

void		circle(t_mlx *app, t_img *img);
void		mandelbrot(t_mlx *app, t_img *img);

#endif
