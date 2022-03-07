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

static char	*conv_ptr(unsigned long long num, unsigned char size)
{
	char	*news;

	news = malloc(sizeof(char) * (size + 3));
	if (!news)
		return (NULL);
	news[0] = '0';
	news[1] = 'x';
	news[size + 2] = 0;
	while (size + 2 > 2)
	{
		news[--size + 2] = "0123456789abcdef"[num % 16];
		num /= 16;
	}
	return (news);
}

char	*conv_hex(unsigned long long num, char type)
{
	unsigned char	digit_size;
	char			*news;

	digit_size = count_digits(num, 16);
	if (type == 'p')
		return (conv_ptr(num, digit_size));
	news = malloc(sizeof(char) * (digit_size + 1));
	if (!news)
		return (NULL);
	news[digit_size] = 0;
	while (digit_size > 0)
	{
		if (type == 'x')
			news[--digit_size] = "0123456789abcdef"[num % 16];
		else
			news[--digit_size] = "0123456789ABCDEF"[num % 16];
		num /= 16;
	}
	return (news);
}
