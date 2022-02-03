/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:26:14 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 11:54:32 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	unsigned char	*s;
	size_t			size_holder;

	p = malloc(size * count);
	s = p;
	size_holder = size;
	while (count * size > 0)
	{
		while (size_holder-- > 0)
			*(s++) = 0;
		size_holder = size;
		count--;
	}
	return (p);
}
