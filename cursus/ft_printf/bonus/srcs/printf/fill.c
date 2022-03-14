#include "ft_printf.h"

void	fill(char *s, char c, size_t len)
{
	size_t itr;

	itr = 0;
	while (itr < len)
		s[itr++] = c;
}
