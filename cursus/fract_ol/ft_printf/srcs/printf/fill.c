/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:28:56 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/27 15:28:56 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill(char *s, char c, size_t len)
{
	size_t	itr;

	itr = 0;
	while (itr < len)
		s[itr++] = c;
}
