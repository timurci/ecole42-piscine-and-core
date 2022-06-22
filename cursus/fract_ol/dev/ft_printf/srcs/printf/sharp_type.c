/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharp_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:23:07 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/27 15:23:08 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*sharp_type(t_shape *shape)
{
	if (shape->flags & 128)
		return ("0X");
	else
		return ("0x");
}
