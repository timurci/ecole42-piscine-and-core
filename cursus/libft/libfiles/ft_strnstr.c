/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:51:22 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 17:23:33 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	scan;
	size_t	nsize;

	if (!*needle)
		return ((char *)haystack);
	nsize = 0;
	while (needle[nsize])
		nsize++;
	scan = 0;
	while (haystack[scan] && scan < len && nsize + scan <= len)
	{
		if (!ft_strncmp(needle, &haystack[scan], nsize))
			return ((char *) &haystack[scan]);
		scan++;
	}
	return (NULL);
}
