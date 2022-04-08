/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:28:37 by tcakmako          #+#    #+#             */
/*   Updated: 2022/04/08 10:57:34 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static unsigned char	count_digits(long *n, char *sign, t_shape *sh, char div)
{
	unsigned char	size;
	long			temp;

	if (*n < 0)
	{
		*n *= -1;
		*sign = '-';
	}
	else
		*sign = '+';
	if (*n == 0)
	{
		if ((sh->flags & (2 | 32)) == 34 && sh->w1 == 0)
			return (0);
		return (1);
	}
	size = 0;
	temp = *n;
	while (temp > 0)
	{
		temp /= div;
		size++;
	}
	return (size);
}

static void	recondition(t_shape *sh, char *type, int ssize)
{
	if (sh->w0 > sh->w1 && sh->flags & 32)
		sh->flags |= 64;
	if (sh->w0 > sh->w1)
		swap_ints(&sh->w0, &sh->w1);
	if (sh->w0 < ssize)
		sh->w0 = ssize;
	if (sh->w1 < ssize)
		sh->w1 = ssize;
	if (*type == 'c')
		sh->flags = sh->flags & 4;
	else if (*type == 'u')
		sh->flags = (sh->flags | (2 | 16)) ^ (2 | 16);
	if (sh->flags & 32)
		sh->flags = (sh->flags | 8) ^ 8;
	if (sh->flags & 4)
		sh->flags = (sh->flags | 8) ^ 8;
	if (sh->flags & 2)
		sh->flags = (sh->flags | 16) ^ 16;
	if ((sh->flags & (2 | 16) && ((sh->flags & 96) == 32 || sh->w1 == ssize)))
		sh->w1++;
	if (sh->flags & 8 || sh->flags & 32)
		*type = '0';
	else
		*type = ' ';
}

static char	*reshape(char *s, t_shape *sh, char sign, char type)
{
	char	*news;

	recondition(sh, &type, sh->slen);
	news = ft_calloc((sh->w1 + 1), sizeof(char));
	if (!news)
		return (NULL);
	fill(news, ' ', sh->w1);
	if (sh->flags & 64 && !(sh->flags & 4))
		fill(&news[sh->w1 - sh->w0], type, sh->w0);
	else if (sh->flags & 64 && sh->flags & 4)
		fill(&news[!(!(sh->flags & (16 | 2)))], type, sh->w0);
	else
		fill(&news[!(!(sh->flags & (16 | 2)))], type, sh->w1);
	if ((sh->flags & 6) / 5 || (sh->flags & 98) == 34 || (sh->flags & 10) / 9)
		news[0] = sign;
	else if (sh->flags & 2)
		news[sh->w1 - sh->w0 - 1] = sign;
	if ((sh->flags & (4 | 32 | 64)) == 36)
		ft_memcpy(&news[sh->w1 - sh->slen], s, sh->slen);
	else if ((sh->flags & (4 | 32)) == 36 || sh->flags & 4)
		ft_memcpy(&news[!(!(sh->flags & 18)) + sh->w0 - sh->slen], s, sh->slen);
	else
		ft_memcpy(&news[sh->w1 - sh->slen], s, sh->slen);
	free(s);
	return (nullp_checker(news, sh, 'i'));
}

static char	*conv_chr(long num, t_shape *sh)
{
	char	*news;

	sh->w1 = 0;
	news = malloc(sizeof(char) * 2);
	if (!news)
		return (NULL);
	news[0] = (unsigned char) num;
	news[1] = 0;
	sh->slen = 1;
	return (reshape(news, sh, 0, 'c'));
}

char	*conv_dec(long num, char type, t_shape *sh)
{
	char			sign;
	unsigned char	digit_size;
	char			*news;

	if (type == 'c')
		return (conv_chr(num, sh));
	digit_size = count_digits(&num, &sign, sh, 10);
	news = malloc(sizeof(char) * (digit_size + 1));
	news[digit_size] = 0;
	while (digit_size > 0)
	{
		news[--digit_size] = num % 10 + 48;
		num /= 10;
	}
	if (sign == '-')
		sh->flags |= 2;
	if (!(sh->flags & (4 | 8)) && sh->w0 > sh->w1
		&& (size_t) sh->w0 > ft_strlen(news))
		sh->flags = (sh->flags | 16) ^ 16;
	if (*news == '0' && (sh-> flags & 32) && !sh->w0 && !sh->w1)
		*news = 0;
	else if (*news == '0' && (sh->flags & 32) && sh->w0 && !sh->w1)
		*news = ' ';
	sh->slen = ft_strlen(news);
	return (reshape(news, sh, sign, type));
}
