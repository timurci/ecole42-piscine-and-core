/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:12 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/05 12:30:07 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char	*ft_strfjoin(char *head, char *tail)
{
	char	*news;
	size_t	scanner;

	if (!head && !tail)
		return (NULL);
	else if (!head)
		return (ft_strdup(tail));
	else if (!tail)
		return (ft_strdup(head));
	news = malloc(sizeof(char) * (ft_strlen(head) + ft_strlen(tail) + 1));
	if (!news)
		return (NULL);
	scanner = 0;
	while (head[scanner++])
		news[scanner - 1] = head[scanner - 1];
	free(head);
	scanner--;
	while (*tail)
		news[scanner++] = *(tail++);
	news[scanner] = 0;
	return (news);
}

char	*ft_strffjoin(char *head, char *tail)
{
	head = ft_strfjoin(head, tail);
	if (tail)
		free(tail);
	return (head);
}
