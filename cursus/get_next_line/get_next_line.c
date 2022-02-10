/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:12:35 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/10 14:36:40 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char static	check_nl(char *buffer, size_t buff_size)
{
	size_t	size;

	size = 0;
	while (size <= buff_size)
	{
		if (buffer[size] == '\n')
		{
			buffer[size + 1] = 0;
			return (1);
		}
		size++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*store;
	char	is_nl;

	buffer = alloc_str("", BUFFER_SIZE);
	store = alloc_str("", 1);
	if (!buffer)
		return (NULL);
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		is_nl = check_nl(buffer, BUFFER_SIZE);
		store = realloc_str(store, buffer);
		if (is_nl)
			break ;
	}
	return (store);
}
