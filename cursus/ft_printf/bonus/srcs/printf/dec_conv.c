#include <stdlib.h>
#include "ft_printf.h"

static unsigned char	count_digits(long *num, char *sign, char div)
{
	unsigned char	size;
	long			temp;

	if (*num == 0)
		return (1);
	if (*num < 0)
	{
		*num *= -1;
		*sign = '-';
	}
	else
		*sign = '+';
	size = 0;
	temp = *num;
	while (temp > 0)
	{
		temp /= div;
		size++;
	}
	return (size);
}

static void	recondition(t_shape *shape, char *type, char *str)
{
	if (shape->width_0 > shape->width_1 && shape->flags & 32)
		shape->flags |= 64;
	if (shape->width_0 > shape->width_1)
		swap_ints(&shape->width_0, &shape->width_1);
	if ((size_t) shape->width_0 < ft_strlen(str))
		shape->width_0 = ft_strlen(str);
	if ((size_t) shape->width_1 < ft_strlen(str))
		shape->width_1 = ft_strlen(str);
	if (*type == 'c')
		shape->flags = shape->flags & 4;
	else if (*type == 'u')
		shape->flags = (shape->flags | (2 | 16)) ^ (2 | 16);
	if (shape->flags & 32)
		shape->flags = (shape->flags | (4 | 8)) ^ (4 | 8);
	if (shape->flags & 4)
		shape->flags = (shape->flags | (8 | 16)) ^ (8 | 16);
	if (shape->flags & (2 | 8))
		shape->flags = (shape->flags | 16) ^ 16;
	if ((shape->flags & 2 && shape->flags & 32 && !(shape->flags & 64))
		|| shape->flags & 16)
		shape->width_1++;
	if (shape->flags & 8 || shape->flags & 32)
		*type = '0';
	else
		*type = ' ';
}

static char	*reshape(char *s, t_shape *shape, char sign, char type)
{
	char	*news;
	size_t	scan;

	recondition(shape, &type, s);
	news = ft_calloc((shape->width_1 + 1), sizeof(char));
	if (!news)
		return (NULL);
	scan = 0;
	fill(news, ' ', shape->width_1);
	if (shape->flags & 64)
		fill(&news[shape->width_1 - shape->width_0], type, shape->width_0);
	else
		fill(news, type, shape->width_0);
	if (shape->flags & 2 && shape->flags & 64)
		news[shape->width_1 - shape->width_0 - 1] = sign;
	else if (shape->flags & 2)
		news[0] = sign;
	if (shape->flags & 4)
		ft_memcpy(&news[sign / (sign - 1)], s, ft_strlen(s));
	else
		ft_memcpy(&news[shape->width_1 - ft_strlen(s)], s, ft_strlen(s));
	free(s);
	return (news);
}

static char	*conv_chr(long num, t_shape *shape)
{
	char	*news;

	shape->width_1 = 0;
	news = malloc(sizeof(char) * 2);
	if (!news)
		return (NULL);
	news[0] = (char) num;
	news[1] = 0;
	return (reshape(news, shape, 0, 'c'));
}

char	*conv_dec(long num, char type, t_shape *shape)
{
	char			sign;
	unsigned char	digit_size;
	char			*news;

	if (type == 'c')
		return(conv_chr(num, shape));
	digit_size = count_digits(&num, &sign, 10);
	news = malloc(sizeof(char) * (digit_size + 1));
	if (!news)
		return (NULL);
	news[digit_size] = 0;
	while (digit_size > 0)
	{
		news[--digit_size] = num % 10 + 48;
		num /= 10;
	}
	if (sign == '-')
		shape->flags |= 2;
	return (reshape(news, shape, sign, type));
}
