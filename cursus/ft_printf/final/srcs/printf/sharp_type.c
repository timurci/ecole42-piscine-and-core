#include "ft_printf.h"

char	*sharp_type(t_shape *shape)
{
	if (shape->flags & 128)
		return ("0X");
	else
		return ("0x");
}
