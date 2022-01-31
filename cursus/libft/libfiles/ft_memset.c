/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:47:04 by tcakmako          #+#    #+#             */
/*   Updated: 2022/01/31 14:35:49 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			scan;
	unsigned char	*r;
	unsigned char	octet;

	scan = 0;
	r = (unsigned char *) b;
	octet = (unsigned char) c;
	while (scan < len)
		r[scan++] = octet;
	return (b);
}
