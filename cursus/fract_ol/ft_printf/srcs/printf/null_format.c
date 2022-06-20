/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:22:56 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/27 18:34:58 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*nullp_checker(char *s, t_shape *sh, char type)
{
	int		scan;

	scan = 1;
	if (*s == 0 && sh->w1 == 1 && type != 'i')
	{
		sh->w1 = 0;
		return (s);
	}
	return (s);
}
