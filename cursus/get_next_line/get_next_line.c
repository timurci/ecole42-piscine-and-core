/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:48:23 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/14 16:51:01 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_remains(char **remains)
{
	if (*remains)
		free(*remains);
	*remains = 0;
}

char	check_nl(char **store, char **remains)
{
	size_t	offset;
	size_t	pos_nl;
	char	has_nl;

	offset = 0;
	pos_nl = 0;
	has_nl = 0;
	while ((*store)[offset])
	{
		if ((*store)[offset] == '\n' && !has_nl)
		{
			pos_nl = offset;
			has_nl = 1;
		}
		offset++;
	}
	if (has_nl)
	{
		*remains = replace_str(*remains, &(*store)[pos_nl + 1]);
		(*store)[pos_nl + 1] = 0;
		*store = replace_str(*store, *store);
	}
	return (has_nl);
}

char	*get_next_line(int fd)
{
	char static	*remains = 0;
	char		*store;
	char		*buffer;

	store = 0;
	buffer = 0;
	if (remains)
		store = replace_str(store, remains);
	else
		store = ft_calloc(1);
	buffer = ft_calloc(BUFFER_SIZE + 1);
	if (!buffer || !store || fd < 0 || fd > 1000 || check_nl(&store, &remains))
		return (check_cd(store, buffer, fd));
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		store = ft_strfjoin(store, buffer);
		if (check_nl(&store, &remains))
			return (check_cd(store, buffer, fd));
	}
	clear_remains(&remains);
	return (check_cd(store, buffer, fd));
}
