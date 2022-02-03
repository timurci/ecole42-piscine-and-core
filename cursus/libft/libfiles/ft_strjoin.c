/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:49:35 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 12:00:34 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	char	*scan;
	size_t	s1size;
	size_t	s2size;

	s1size = 0;
	while (s1[s1size])
		s1size++;
	s2size = 0;
	while (s2[s2size])
		s2size++;
	p = malloc(sizeof(char) * (s1size + s2size + 1));
	if (!p)
		return (NULL);
	scan = p;
	while (*s1)
		*(scan++) = *(s1++);
	while (*s2)
		*(scan++) = *(s2++);
	*scan = 0;
	return (p);
}
