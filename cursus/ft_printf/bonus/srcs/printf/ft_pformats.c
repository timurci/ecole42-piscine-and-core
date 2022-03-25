/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pformats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:20 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/25 14:30:51 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "ft_printf.h"

static char	check_set(char c, char *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

static long	loc_set(char *s, size_t mem, t_shape *shape)
{
	alter_shape(shape, 0, 0, 0);
	while (s[mem])
	{
		if (t1_checker(shape, s[mem]) == -1)
			return (-1);
		else if (check_set(s[mem], TYPE2TOKENS))
			return (mem);
		mem++;
	}
	return (-1);
}

static char	*get_type(char *tn, va_list ap, t_shape *shape)
{
	if (!ft_tkncmp(tn, "p"))
		return (conv_hex(va_arg(ap, unsigned long long), 'p', shape));
	else if (!ft_tkncmp(tn, "s"))
		return (conv_str(va_arg(ap, char *), shape));
	else if (!ft_tkncmp(tn, "d") || !ft_tkncmp(tn, "i") || !ft_tkncmp(tn, "c"))
		return (conv_dec(va_arg(ap, int), *tn, shape));
	else if (!ft_tkncmp(tn, "u"))
		return (conv_dec(va_arg(ap, unsigned int), *tn, shape));
	else if (!ft_tkncmp(tn, "x") || !ft_tkncmp(tn, "X"))
		return (conv_hex(va_arg(ap, unsigned long long), *tn, shape));
	else if (!ft_tkncmp(tn, "%"))
		return (ft_strdup("%"));
	return (NULL);
}

long	pformat(const char *input, long mem, char **store, va_list ap)
{
	long	end;
	char	*typeholder;
	t_shape	shape;

	if (input[mem] == '%')
		mem++;
	end = loc_set((char *) input, mem, &shape);
	if (end < 0)
		return (-1);
	typeholder = get_type((char *) &input[end], ap, &shape);
	if (!typeholder)
		return (-1);
	*store = ft_strffjoin(*store, typeholder);
	return (end + 1);
}
