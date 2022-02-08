/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:49:59 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/08 13:01:27 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	scan;
	size_t	slen;

	if (start > ft_strlen(s))
	{
		p = (char *) malloc(sizeof(char) * 1);
		if (!p)
			return (NULL);
		*p = 0;
		return (p);
	}
	p = (char *) malloc(sizeof(char) * len);
	if (!p)
		return (NULL);
	scan = 0;
	s = &s[start];
	slen = ft_strlen(s);
	while (scan < len && scan < slen)
		p[scan++] = *(s++);
	return (p);
}
