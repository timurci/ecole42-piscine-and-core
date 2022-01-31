#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	scan;

	scan = 0;
	while (scan < n)
		((int *) s)[scan++] = 0;
}
