/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:24:24 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/02 17:24:25 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_echo(char **argv)
{
	char	trail;

	argv++;
	trail = 1;
	if (*argv && !ft_strcmp(*argv, "-n"))
	{
		trail = 0;
		argv++;
	}
	while (*argv)
	{
		write(1, *argv, ft_strlen(*argv));
		if (*(argv + 1))
			write(1, " ", 1);
		argv++;
	}
	if (trail)
		write(1, "\n", 1);
	return (0);
}
