/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:20:28 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/08 14:04:45 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char static	setcmp(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (0);
		set++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1len;
	char	*p;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && !setcmp(*s1, set))
		s1++;
	s1len = 0;
	while (s1[s1len])
		s1len++;
	while (s1len > 1 && !setcmp(s1[s1len - 1], set))
		s1len--;
	p = malloc(sizeof(char) * (s1len + 1));
	if (!p)
		return (NULL);
	p[s1len] = 0;
	while (s1len-- > 1)
		p[s1len] = s1[s1len];
	p[s1len] = s1[s1len];
	return (p);
}
