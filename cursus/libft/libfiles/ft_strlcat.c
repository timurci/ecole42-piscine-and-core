/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:44:34 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/02 12:48:24 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	scan;
	size_t	dlen;
	size_t	slen;

	scan = 0;
	while (dst[scan])
		scan++;
	dlen = scan;
	slen = 0;
	while (src[slen])
		slen++;
	if (dsize <= dlen)
		return (dsize + slen);
	while (*src && scan < dsize - 1)
		dlen[scan++] = *(src++);
	dlen[scan] = 0;
	return (dlen + slen);
}
