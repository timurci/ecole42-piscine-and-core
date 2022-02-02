/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:28:59 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/02 17:01:57 by tcakmako         ###   ########.fr       */
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
	dup = (char *) malloc(sizeof(char) * (ssize + 1));
	if (!dup)
		return (NULL);
	ssize = 0;
	while (*s1)
		dup[ssize++] = *(s1++);
	dup[ssize] = 0;
	return (dup);
}
