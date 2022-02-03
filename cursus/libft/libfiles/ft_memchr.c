/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:51:52 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 16:02:32 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	scan;

	scan = 0;
	while (scan++ < n)
	{
		if (*(unsigned char *)s == (unsigned char) c)
			return ((void *)s);
		s++;
	}
	return (NULL);
}
