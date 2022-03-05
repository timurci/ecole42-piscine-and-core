/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pformats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:20 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/05 14:45:46 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "ft_printf.h"

char static	check_set(char c, char *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

size_t static	loc_set(char *s, char *set, size_t mem, int *width)
{
	while (s[mem])
	{
		if (ft_isdigit(s[mem]))
			*width = *width * 10 + (s[mem] - 48);
		else if (check_set(s[mem], set))
			return (mem);
		else if (*width)
			return (-1);
		mem++;
	}
	return (-1);
}

char static	*get_type(char *tn, va_list ap, int width)
{
	void			*p;
	int				d;
	unsigned int	u;

	if (!ft_tkncmp(tn, "p") || !ft_tkncmp(tn, "s"))
	{
		p = va_arg(ap, void *);
		if (*tn == 's')
			return (conv_str(p, width));
		else
			return (conv_hex((long) p, 1, width));
	}
	else if (!ft_tkncmp(tn, "d") || !ft_tkncmp(tn, "i") || !ft_tkncmp(tn, "c"))
	{
		d = va_arg(ap, int);
		return (conv_dec(d, *tn / 100, width));
	}
	else if (!ft_tkncmp(tn, "u") || !ft_tkncmp(tn, "x") || !ft_tkncmp(tn, "X"))
	{
		u = va_arg(ap, unsigned int);
		if (*tn == 'u')
			return (conv_dec(u, *tn / 100, width));
		return (conv_hex(u, *tn / 120, width));
	}
	return (NULL);
}

size_t	pformat(const char *input, size_t mem, char **store, va_list ap)
{
	size_t	end;
	int		width;
	char	*typeholder;
	char	*garbage_collector;

	if (input[mem] == '%')
		mem++;
	end = loc_set((char *) input, TYPE2TOKENS, mem, &width);
	if (end < 0)
		return (-1);
	if (!ft_tkncmp((char *) &input[end], "%"))
		typeholder = ft_strdup("%");
	else
		typeholder = get_type((char *) &input[end], ap, width);
	if (!typeholder)
		return (-1);
	garbage_collector = *store;
	*store = ft_strffjoin(ft_substr(*store, 0, mem - 1), typeholder);
	free(garbage_collector);
	return (end + 1);
}
