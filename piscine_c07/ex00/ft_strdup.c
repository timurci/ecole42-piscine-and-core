#include <stdlib.h>

char	*ft_strdup(char *src)
{
	unsigned int	i;
	unsigned int	size;
	char			*news;

	i = 0;
	while (src[i])
		i++;
	size = i;
	news = (char *) malloc(size + 1);
	i = 0;
	while (i < size)
	{
		news[i] = src[i];
		i++;
	}
	news[i] = 0;
	return (news);
}
