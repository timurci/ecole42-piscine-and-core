/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:03:35 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 11:56:54 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*memmove(void *dst, const void *src, size_t len)
{
	size_t			scan;
	unsigned char	*dp;
	unsigned char	*sp;

	dp = NULL;
	sp = NULL;
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
		while (scan > len)
		{
			dp[scan - 1] = sp[scan - 1];
			scan--;
		}
	}
	return (dst);
}
