/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:45 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/05 14:08:35 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"

/*controls are not optimal due to norminette limitations.
 *ln14 check store && input
 *ln24 check store
 *
 */

int	check_cd(size_t mem, char **store)
{
	int	ret_value;

	if (mem < 0 || !*store)
	{
		if (*store)
			free(*store);
		return (-1);
	}
	else
	{
		ret_value = ft_strlen(*store);
		write(1, *store, ret_value);
		free(*store);
		*store = 0;
		return (ret_value);
	}
}

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	size_t	scan;
	size_t	mem;
	char	*store;

	va_start(ap, input);
	scan = 0;
	mem = 0;
	store = 0;
	while (input[scan])
	{
		if (input[scan] == '%')
		{
			store = ft_strffjoin(store, ft_substr(input, mem, scan - mem));
			mem = pformat(input, scan, &store, ap);
			if (mem < 0)
				return (check_cd(mem, &store));
			scan = mem;
			continue ;
		}
		scan++;
	}
	store = ft_strffjoin(store, ft_substr(input, mem, scan - mem));
	va_end(ap);
	return (check_cd(mem, &store));
}
