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

static void	recondition(t_shape *shape, char *type, size_t ssize)
{
	if (shape->w0 > shape->w1 && shape->flags & 32)
		shape->flags |= 64;
	if (shape->w0 > shape->w1)
		swap_ints(&shape->w0, &shape->w1);
	if ((size_t) shape->w0 < ssize)
		shape->w0 = ssize;
	if ((size_t) shape->w1 < ssize)
		shape->w1 = ssize;
	if (*type == 'c')
		shape->flags = shape->flags & 4;
	else if (*type == 'u')
		shape->flags = (shape->flags | (2 | 16)) ^ (2 | 16);
	if (shape->flags & 32)
		shape->flags = (shape->flags | 8) ^ 8;
	if (shape->flags & 4)
		shape->flags = (shape->flags | (8 | 16)) ^ (8 | 16);
	if (shape->flags & (2 | 8))
		shape->flags = (shape->flags | 16) ^ 16;
	if ((shape->flags & 2 && ((shape->flags & 32 && !(shape->flags & 64))
		|| (size_t) shape->w1 == ssize)) || shape->flags & 16)
		shape->w1++;
	if (shape->flags & 8 || shape->flags & 32)
		*type = '0';
	else
		*type = ' ';
}

static char	*reshape(char *s, t_shape *sh, char sign, char type, size_t slen)
{
	char	*news;

	recondition(sh, &type, slen);
	news = ft_calloc((sh->w1 + 1), sizeof(char));
	if (!news)
		return (NULL);
	fill(news, ' ', sh->w1);
	if (sh->flags & 64 && !(sh->flags & 4))
		fill(&news[sh->w1 - sh->w0], type, sh->w0);
	else if (sh->flags & 64 && sh->flags & 4)
		fill(&news[sign / '-'], type, sh->w0);
	else
		fill(news, type, sh->w1);
	if ((sh->flags & 6) / 5 || (sh->flags & 98) == 34 || (sh->flags & 10) / 9)
		news[0] = sign;
	else if (sh->flags & 2)
		news[sh->w1 - sh->w0 - 1] = sign;
	if ((sh->flags & (4 | 32 | 64)) == 36)
		ft_memcpy(&news[sh->w1 - slen], s, slen);
	else if ((sh->flags & (4 | 32)) == 36 || sh->flags & 4)
		ft_memcpy(&news[sign / '-' + sh->w0 - slen], s, slen);
	else
		ft_memcpy(&news[sh->w1 - slen], s, slen);
	free(s);
	return (news);
}

static char	*conv_chr(long num, t_shape *shape)
{
	char	*news;

	shape->w1 = 0;
	news = malloc(sizeof(char) * 2);
	if (!news)
		return (NULL);
	news[0] = (char) num;
	news[1] = 0;
	if (!news[0])
		shape->w0--;
	return (reshape(news, shape, 0, 'c', ft_strlen(news)));
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
	if (*news == '0' && (shape-> flags & 32) && !shape->w0 && !shape->w1)
		*news = 0;
	else if (*news == '0' && (shape->flags & 32) && shape->w0 && !shape->w1)
		*news = ' ';
	return (reshape(news, shape, sign, type, ft_strlen(news)));
}
