/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:03:35 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 15:22:29 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			scan;
	unsigned char	*dp;
	unsigned char	*sp;

	dp = (unsigned char *) dst;
	sp = (unsigned char *) src;
	scan = 0;
	if ((unsigned int) dst < (unsigned int) src)
	{
		while (scan < len)
		{
			dp[scan] = sp[scan];
			scan++;
		}
	}
	else if ((unsigned int) dst > (unsigned int) src)
	{
		scan = len;
		while (scan > 0)
		{
			dp[scan - 1] = sp[scan - 1];
			scan--;
		}
	}
	return (dst);
}
