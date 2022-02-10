/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:12:38 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/10 14:29:32 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*alloc_str(char *buffer, size_t memsize)
{
	size_t	size;
	char	*ns;

	if (memsize == 0)
	{
		size = 0;
		while (buffer[size])
			size++;
	}
	else
		size = memsize ;
	ns = malloc(sizeof(char) * (size + 1));
	if (!ns)
		return (NULL);
	size = 0;
	while (size < memsize)
	{
		if (*buffer)
			ns[size++] = *(buffer++);
		else
			ns[size++] = 0;
	}
	ns[size] = 0;
	return (ns);
}

char	*realloc_str(char *base, char *tail)
{
	size_t	bsize;
	size_t	tsize;
	char	*ns;

	bsize = 0;
	tsize = 0;
	while (base[bsize])
		bsize++;
	while (tail[tsize])
		tsize++;
	ns = malloc(sizeof(char) * (bsize + tsize + 1));
	bsize = 0;
	while (*base)
		ns[bsize++] = *(base++);
	free (base);
	while (*tail)
		ns[bsize++] = *(tail++);
	ns[bsize] = 0;
	return (ns);
}
