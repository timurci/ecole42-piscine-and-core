#include <stdlib.h>
#include "ft_printf.h"

char	*ft_strfjoin(char *head, char *tail)
{
	char	*news;
	size_t	scanner;

	if (!head && !tail)
		return (NULL);
	else if (!head)
		ft_strdup(tail);
	else if (!tail)
		ft_strdup(head);
	news = malloc(sizeof(char) * (ft_strlen(head) + ft_strlen(tail) + 1));
	if (!news)
		return (NULL);
	scanner = 0;
	while (head[scanner++])
		news[scanner - 1] = head[scanner - 1];
	free(head);
	scanner--;
	while (tail)
		news[scanner++] = *(tail++);
	return (news);
}

char	*ft_strffjoin(char *head, char *tail)
{
	head = ft_strfjoin(head, tail);
	if (tail)
		free(tail);
	return (head);
}
