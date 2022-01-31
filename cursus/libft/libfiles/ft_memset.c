#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	scan;

	scan = 0;
	while (scan < len)
		((int *) b)[scan++] = c;
	return (b);
}
