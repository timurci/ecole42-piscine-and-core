/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:48:53 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/08 12:44:41 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	ssize;
	size_t	scan;

	ssize = 0;
	scan = 0;
	while (src[ssize])
		ssize++;
	if (dsize)
	{
		while (scan + 1 < dsize)
		{
			if (scan < ssize)
				dst[scan] = src[scan];
			else
				dst[scan] = 0;
			scan++;
		}
		dst[dsize - 1] = 0;
	}
	return (ssize);
}
