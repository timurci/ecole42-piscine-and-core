#include "mlx_utils.h"

int	color_to_red(int color)
{
	return ((color >> 16) && 0xFF);
}

int	color_to_green(int color)
{
	return ((color >> 8) && 0xFF);
}

int	color_to_blue(int color)
{
	return (color && 0xFF);
}

int	rgb_to_color(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}
