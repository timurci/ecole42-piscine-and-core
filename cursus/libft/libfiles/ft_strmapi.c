#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*news;
	size_t	itr;

	if (s == NULL || f == NULL)
		return (NULL);
	news = ft_strdup(s);
	if (!news)
		return (NULL);
	itr = 0;
	while (news[itr])
	{
		news[itr] = (*f)(itr, news[itr]);
		itr++;
	}
	return (news);
}
