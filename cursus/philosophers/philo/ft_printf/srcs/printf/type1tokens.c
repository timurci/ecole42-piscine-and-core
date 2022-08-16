/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type1tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:29:06 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/27 15:29:07 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	alter_shape(t_shape *shape, int w0, int w1, char fl)
{
	shape->w0 = w0;
	shape->w1 = w1;
	shape->flags = fl;
}

static char	check_set(char c, char *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

static char	valid_expression(t_shape *shape, char c)
{
	char	is_token;

	is_token = check_set(c, TYPE1TOKENS);
	if (ft_isdigit(c))
		return (1);
	else if (is_token && (c == 0 || (c == '.' && (shape->flags & 32))))
		return (1);
	else if (is_token && !shape->w0 && !(shape->flags & 32))
		return (1);
	else
		return (0);
}

char	t1_checker(t_shape *shape, char c)
{
	if (c == '#')
		shape->flags = shape->flags | 1;
	else if (c == '+')
		shape->flags = shape->flags | 2;
	else if (c == '-')
		shape->flags = shape->flags | 4;
	else if (c == '0' && !shape->w0 && !(shape->flags & 32))
		shape->flags = shape->flags | 8;
	else if (c == ' ')
		shape->flags = shape->flags | 16;
	else if (c == '.' && !(shape->flags & 32))
		shape->flags = shape->flags ^ 32;
	else if (ft_isdigit(c))
	{
		if (shape->flags & 32)
			shape->w1 = shape->w1 * 10 + (c - 48);
		else
			shape->w0 = shape->w0 * 10 + (c - 48);
	}
	else
		return (2);
	if (valid_expression(shape, c))
		return (0);
	return (-1);
}
