/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:51:22 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/02 11:51:23 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*checkp;

	if (!*needle)
		return ((char *)haystack);
	checkp = NULL;
	while (*haystack && len-- > 0)
	{
		if (!ft_strcmp(needle, haystack))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
