/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:21:42 by tcakmako          #+#    #+#             */
/*   Updated: 2022/04/04 17:15:51 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static unsigned char	count_digits(unsigned long long num, char div)
{
	unsigned char	size;

	if (num == 0)
		return (1);
	size = 0;
	while (num > 0)
	{
		num /= div;
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
	if (shape->flags & 32)
		shape->flags = (shape->flags | 8) ^ 8;
	if (shape->flags & 4)
		shape->flags = (shape->flags | (8 | 16)) ^ (8 | 16);
	if ((shape->flags & 1 && (((size_t) shape->w1 < ssize + 2)
				|| shape->flags & (32 | 64) == 32))
		shape->w1 = ssize + 2;
	if (shape->flags & (8 | 32))
		*type = '0';
	else
		*type = ' ';
}

static char	*reshape(char *s, t_shape *sh, char type, size_t slen)
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
		fill(&news[(sh->flags & 1) * 2], type, sh->w0);
	else
		fill(news, type, sh->w1);
	if ((sh->flags & 1) && (sh->flags & (4 | 8) || (sh->flags & 96) == 32))
		ft_memcpy(news, sharp_type(sh), 2);
	else if (sh->flags & 1)
		ft_memcpy(&news[sh->w1 - sh->w0 - 2], sharp_type(sh), 2);
	if ((sh->flags & (4 | 32 | 64)) == 36)
		ft_memcpy(&news[sh->w1 - slen], s, slen);
	else if ((sh->flags & (4 | 32)) == 36 || sh->flags & 4)
		ft_memcpy(&news[(sh->flags & 1) * 2 + sh->w0 - slen], s, slen);
	else
		ft_memcpy(&news[sh->w1 - slen], s, slen);
	free(s);
	return (nullp_checker(news, sh, 'h'));
}

static char	*conv_ptr(unsigned long long num, t_shape *sh, unsigned char size)
{
	char	*news;

	sh->flags |= 1;
	news = malloc(sizeof(char) * (size + 1));
	if (!news)
		return (NULL);
	news[size] = 0;
	while (size > 0)
	{
		news[--size] = "0123456789abcdef"[num % 16];
		num /= 16;
	}
	return (reshape(news, sh, 'p', ft_strlen(news)));
}

char	*conv_hex(unsigned long long num, char type, t_shape *sh)
{
	unsigned char	digit_size;
	char			*news;

	digit_size = count_digits(num, 16);
	if (type == 'p')
		return (conv_ptr(num, sh, digit_size));
	if (type == 'X')
		sh->flags |= 128;
	if (num == 0)
		sh->flags = (sh->flags | 1) ^ 1;
	if (num == 0 && (sh->flags & 32) && !sh->w1 && sh->w0)
		return (reshape(ft_strdup(" "), sh, type, 1));
	else if (num == 0 && (sh->flags & 32) && !sh->w1)
		return (reshape(ft_strdup(""), sh, type, 1));
	news = malloc(sizeof(char) * (digit_size + 1));
	news[digit_size] = 0;
	while (digit_size > 0)
	{
		if (type == 'x')
			news[--digit_size] = "0123456789abcdef"[num % 16];
		else
			news[--digit_size] = "0123456789ABCDEF"[num % 16];
		num /= 16;
	}
	return (reshape(news, sh, type, ft_strlen(news)));
}
