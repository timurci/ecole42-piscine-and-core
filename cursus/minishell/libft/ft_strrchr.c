/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:40:39 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/03 15:16:07 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*intl;

	intl = (char *)s;
	while (*s)
		s++;
	while (!(s == intl))
	{
		if (*s == (char) c)
			return ((char *) s);
		s--;
	}
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}
