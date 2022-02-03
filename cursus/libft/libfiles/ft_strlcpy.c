/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:48:53 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 12:00:57 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	ssize;

	ssize = 0;
	while (src[ssize])
		ssize++;
	while (dsize-- > 1)
	{
		if (*src)
			*(dst++) = *(src++);
		else
			*(dst++) = 0;
	}
	*dst = 0;
	return (ssize);
}
