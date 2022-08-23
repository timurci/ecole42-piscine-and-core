/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:41:23 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/18 12:41:41 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	scan;

	scan = 0;
	if (size > 0)
	{
		while (src[scan] && scan + 1 < size)
		{
			dst[scan] = src[scan];
			scan++;
		}
		dst[scan] = 0;
	}
	while (src[scan])
		scan++;
	return (scan);
}
