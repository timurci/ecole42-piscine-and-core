#include <stdlib.h>

char	*ft_strdup(char *s)
{
	char	*news;
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	news = malloc(sizeof(*news) * (len + 1));
	if (!news)
		return (NULL);
	news[len] = 0;
	while (len-- > 0)
		news[len] = s[len];
	return (news);
}
