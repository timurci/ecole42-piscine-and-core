/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:32:56 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/02 17:02:32 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	cdigits(int n)
{
	char	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

unsigned int	ft_ft_pow10(char power)
{
	unsigned int	result;

	result = 1;
	while (power-- > 0)
		result *= 10;
	return (result);
}

static void	build_str(int n, char is_neg, char *str, char digits)
{
	if (is_neg)
		*(str++) = '-';
	while (digits > 0)
		*(str++) = (n / ft_ft_pow10(digits-- - 1) % 10) + 48;
	*str = 0;
}

char	*ft_itoa(int n)
{
	char	digits;
	char	is_neg;
	char	*news;

	if (n == -2147483648)
	{
		news = ft_strdup("-2147483648");
		return (news);
	}
	if (n < 0)
	{
		is_neg = 1;
		n *= -1;
	}
	else
		is_neg = 0;
	digits = cdigits(n);
	news = malloc(sizeof(char) * (digits + is_neg + 1));
	if (!news)
		return (NULL);
	build_str(n, is_neg, news, digits);
	return (news);
}
