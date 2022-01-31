#include <stdlib.h>

void	*memchr(const void *s, int c, size_t n)
{
	if (!n)
		return (NULL);
	while (n-- > 0 && *s)
	{
		if (*s == (unsigned char) c)
			return(s);
		s++;
	}
	if (*s == (unsigned char) c)
		return (s);
	return (NULL);
}
