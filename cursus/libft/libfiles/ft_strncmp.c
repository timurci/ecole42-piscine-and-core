/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:51:08 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/08 12:12:05 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			scan;
	unsigned char	*u1;
	unsigned char	*u2;

	u1 = (unsigned char *) s1;
	u2 = (unsigned char *) s2;
	scan = 0;
	while (scan < n && s1[scan])
	{
		if (u1[scan] != u2[scan])
			break ;
		scan++;
	}
	if (scan == n)
		scan -= 1;
	return ((int) u1[scan] - u2[scan]);
}
