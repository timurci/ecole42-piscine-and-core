/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:49:59 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/10 12:34:50 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	scan;
	size_t	slen;

	if (!s || start > ft_strlen(s))
	{
		p = (char *) malloc(sizeof(char) * 1);
		if (!p)
			return (NULL);
		*p = 0;
		return (p);
	}
	scan = 0;
	s = &s[start];
	slen = ft_strlen(s);
	p = (char *) malloc(sizeof(char) * (slen + 1));
	if (!p)
		return (NULL);
	while (scan < len && scan < slen)
		p[scan++] = *(s++);
	p[scan] = 0;
	return (p);
}
