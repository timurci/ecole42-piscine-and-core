/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:28:59 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/02 12:29:00 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	ssize;
	char	*dup;

	ssize = 0;
	while (s1[ssize])
		ssize++;
	dup = (char *) malloc(sizeof(char) * ssize);
	if (!dup)
		return (NULL);
	while (*s1)
		*(dup++) = *(s1++);
	*dup = 0;
	return (dup);
}
