/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:20:28 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 12:02:11 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int static	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	if (!*s1)
		return (*(s1 - 1) - *(s2 - 1));
	return (*s1 - *s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	set_size;
	size_t	s1len;
	char	*p;

	set_size = 0;
	while (set[set_size])
		set_size++;
	while (*s1 && !ft_strcmp(set, s1))
		s1 += set_size;
	s1len = 0;
	while (s1[s1len])
		s1len++;
	while (s1len - set_size > 0 && !ft_strcmp(set, &s1[s1len - set_size]))
		s1len -= set_size;
	p = malloc(sizeof(char) * (s1len + 1));
	if (!p)
		return (NULL);
	p[s1len] = 0;
	while (s1len-- > 1)
		p[s1len] = s1[s1len];
	p[s1len] = s1[s1len];
	return (p);
}
