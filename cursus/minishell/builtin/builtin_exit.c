/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:42:00 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/02 17:42:01 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_exit(t_shell *shell, void *param)
{
	if (param)
		write(1, "exit\n", 5);
	shell_destroy(shell);
	exit(EXIT_SUCCESS);
	return (0);
}
