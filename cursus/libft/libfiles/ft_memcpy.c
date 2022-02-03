/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:03:45 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 11:56:38 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			scan;
	unsigned char	*dp;
	unsigned char	*sp;

	scan = 0;
	dp = (unsigned char *) dst;
	sp = (unsigned char *) src;
	while (scan < n)
	{
		dp[scan] = sp[scan];
		scan++;
	}
	return (dst);
}
