/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:02:12 by ademirci          #+#    #+#             */
/*   Updated: 2022/09/24 18:16:59 by alperdemirci     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	operator_or(t_shell *shell, int i)
{
	int	j;
	int	c;

	j = -1;
	c = i;
	while (--c >= 0)
		if (shell->cmds[c].wait_ctrl == 0)
			break ;
	j = c - 1;
	while (++j < i)
		if (shell->cmds[j].is_sucex == 0)
			return (0);
	return (1);
}

int	operator_and(t_shell *shell, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (shell->cmds[j].is_sucex == 0)
			return (1);
	}
	return (0);
}

int	command_check(t_shell *shell, int i)
{
	if (shell->cmds[i].cmd != NULL && !is_wait(shell->cmds[i]))
		return (1);
	if (shell->cmds[i].cmd != NULL && shell->cmds[i].wait_ctrl == 0)
		return (operator_and(shell, i));
	if (shell->cmds[i].cmd != NULL && shell->cmds[i].wait_ctrl == 1)
		return (operator_or(shell, i));
	return (0);
}

int	is_wait(t_cmd cmd)
{
	if (cmd.wait_ctrl == 1 || cmd.wait_ctrl == 0)
		return (1);
	return (0);
}

void	wait_list(t_shell *shell, int last)
{
	int	i;

	i = -1;
	while (++i < last)
		wait(&shell->cmds[i].pid);
}
