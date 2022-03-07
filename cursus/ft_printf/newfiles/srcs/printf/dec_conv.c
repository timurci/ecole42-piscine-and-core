#include <stdlib.h>
#include "ft_printf.h"

static unsigned char	count_digits(long num, char div)
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

static char	*conv_chr(long num)
{
	char	*news;

	news = malloc(sizeof(char) * 2);
	if (!news)
		return (NULL);
	news[0] = (char) num;
	news[1] = 0;
	return (news);
}

char	*conv_dec(long num, char type)
{
	char			sign;
	unsigned char	digit_size;
	char			*news;

	if (!type)
		return(conv_chr(num));
	sign = 0;
	if (num < 0)
	{
		num *= -1;
		sign = 1;
	}
	digit_size = count_digits(num, 10);
	news = malloc(sizeof(char) * (digit_size + sign + 1));
	if (!news)
		return (NULL);
	news[digit_size + sign] = 0;
	while (digit_size > 0)
	{
		news[--digit_size + sign] = num % 10 + 48;
		num /= 10;
	}
	if (sign)
		news[0] = '-';
	return (news);
}
