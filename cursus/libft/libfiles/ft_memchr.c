/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:51:52 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 11:56:12 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*memchr(const void *s, int c, size_t n)
{
	if (!n)
		return (NULL);
	while (n-- > 0 && *s)
	{
		if (*s == (unsigned char) c)
			return (s);
		s++;
	}
	if (*s == (unsigned char) c)
		return (s);
	return (NULL);
}
