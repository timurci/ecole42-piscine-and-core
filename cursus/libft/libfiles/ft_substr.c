#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	scan;

	p = (char *) malloc(sizeof(char) * len);
	if (!p)
		return (NULL);
	scan = 0;
	s = &s[start];
	while (scan < len)
		p[scan++] = *(s++);
	return (p);
}
