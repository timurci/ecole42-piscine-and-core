/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:49:59 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 12:02:26 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	scan;

	p = (char *) malloc(sizeof(char) * len);
	if (!p)
		return (NULL);
	scan = 0;
	s = &s[start];
	while (scan < len)
		p[scan++] = *(s++);
	return (p);
}
