/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:45 by tcakmako          #+#    #+#             */
/*   Updated: 2022/04/04 11:47:01 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"

int	check_cd(int mem, int print_len)
{
	if (mem < 0)
		return (-1);
	else
		return (print_len);
}

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int		scan;
	int		mem;
	int		print_len;

	va_start(ap, input);
	scan = 0;
	mem = 0;
	print_len = 0;
	while (input[scan])
	{
		if (input[scan] == '%')
		{
			print_len += write(1, &input[mem], scan - mem);
			mem = pformat(input, scan, &print_len, ap);
			if (mem < 0)
				return (check_cd(mem, print_len));
			scan = mem;
			continue ;
		}
		scan++;
	}
	print_len += write(1, &input[mem], scan - mem);
	va_end(ap);
	return (check_cd(mem, print_len));
}
