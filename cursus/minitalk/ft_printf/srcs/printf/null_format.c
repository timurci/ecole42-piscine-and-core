/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:22:56 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/08 22:25:36 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*nullp_checker(char *s, t_shape *sh, char type)
{
	if (*s == 0 && sh->w1 == 1 && type != 'i')
	{
		sh->w1 = 0;
		return (s);
	}
	return (s);
}
