/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:03:50 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/05 12:51:53 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char static	count_digits(long *num, unsigned char *size, char div)
{
	char			sign;
	long			temp;

	sign = 0;
	*size = 0;
	if (*num == 0)
		*size = 1;
	else if (*num < 0)
	{
		*num *= -1;
		sign = 1;
	}
	temp = *num;
	while (temp > 0)
	{
		temp /= div;
		(*size)++;
	}
	return (sign);
}

char	*conv_dec(long num, char type, int width)
{
	char			sign;
	unsigned char	digit_size;
	char			*news;

	if (type == 0)
		num = (char) num;
	sign = count_digits(&num, &digit_size, 10);
	if (width < digit_size + sign)
		width = 0;
	else
		width -= digit_size + sign;
	news = malloc(sizeof(char) * (digit_size + width + sign + 1));
	if (!news)
		return (NULL);
	news[digit_size + width + sign] = 0;
	while (digit_size > 0)
	{
		news[--digit_size + width + sign] = num % 10;
		num /= 10;
	}
	if (sign)
		news[width] = '-';
	while (width > 0)
		news[--width] = ' ';
	return (news);
}

char	*conv_hex(unsigned int num, char type, int width)
{
	unsigned char	digit_size;
	char			*news;

	count_digits((long *) &num, &digit_size, 16);
	if (width < digit_size)
		width = 0;
	else
		width -= digit_size;
	news = malloc(sizeof(char) * (digit_size + width + 1));
	if (!news)
		return (NULL);
	news[digit_size + width] = 0;
	while (digit_size > 0)
	{
		if (type)
			news[--digit_size + width] = "0123456789abcdef"[num % 16];
		else
			news[--digit_size + width] = "0123456789ABCDEF"[num % 16];
		num /= 16;
	}
	while (width > 0)
		news[--width] = ' ';
	return (news);
}

char	*conv_str(char	*str, int width)
{
	size_t	ssize;
	char	*news;

	ssize = ft_strlen(str);
	if ((long long) width < (long long) ssize)
		width = 0;
	else
		width -= ssize;
	news = malloc(sizeof(char) * (ssize + width + 1));
	if (!news)
		return (NULL);
	ssize = 0;
	while ((long long) ssize < (long long) width)
		news[ssize] = ' ';
	while (*str)
		news[ssize++] = *(str++);
	news[ssize] = 0;
	return (news);
}
