/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:48:30 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/15 13:06:03 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	*ft_calloc(size_t size)
{
	unsigned char	*holder;

	holder = malloc(sizeof(unsigned char) * size);
	if (!holder)
		return (NULL);
	while (size-- > 0)
		holder[size] = 0;
	return ((void *) holder);
}

char	*replace_str(char *old_str, char *new_str)
{
	size_t	size;
	char	*temp;

	if (!new_str)
		return (ft_calloc(1));
	size = 0;
	while (new_str[size])
		size++;
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	temp[size] = 0;
	while (size-- > 0)
	{
		temp[size] = new_str[size];
	}
	if (old_str)
		free(old_str);
	return (temp);
}

char	*ft_strfjoin(char *head, char *tail)
{
	char	*p;
	size_t	hsize;
	size_t	tsize;

	hsize = 0;
	while (head[hsize])
		hsize++;
	tsize = 0;
	while (tail[tsize])
		tsize++;
	p = ft_calloc(sizeof(char) * (hsize + tsize + 1));
	if (!p)
		return (NULL);
	hsize = 0;
	while (head[hsize++])
		p[hsize - 1] = head[hsize - 1];
	hsize--;
	while (*tail)
	{
		p[hsize++] = *tail;
		*(tail++) = 0;
	}
	free(head);
	return (p);
}

char	*check_cd(char *store, char *buffer, int fd)
{
	if (!buffer && !store)
		return (NULL);
	else if (!store || !*store)
	{
		free(buffer);
		if (!*store)
			free(store);
		return (NULL);
	}
	else if (fd < 0 || fd > 256)
	{
		free(buffer);
		free(store);
		return (NULL);
	}
	else
	{
		free(buffer);
		return (store);
	}
}
