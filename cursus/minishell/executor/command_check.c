/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:41:26 by ademirci          #+#    #+#             */
/*   Updated: 2022/10/23 14:57:33 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	operator_or(t_shell *shell, int i)
{
	int	j;
	int	c;

	j = -1;
	c = i;
	while (--c > 0)
		if (shell->cmds[c].wait_ctrl == 0)
			break ;
	j = c;
	while (++j < i)
		if (shell->cmds[j].exit_status == 0)
			return (0);
	return (1);
}

int	operator_and(t_shell *shell, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (shell->cmds[j].exit_status == 0)
			return (1);
	}
	return (0);
}

int	command_check(t_shell *shell, int i)
{
	if (shell->cmds[i].cmd != NULL && !is_wait(&shell->cmds[i]))
		return (1);
	if (shell->cmds[i].cmd != NULL && shell->cmds[i].wait_ctrl == 0)
		return (operator_and(shell, i));
	if (shell->cmds[i].cmd != NULL && shell->cmds[i].wait_ctrl == 1)
		return (operator_or(shell, i));
	if (is_assignment(&shell->cmds[i]))
		return (1);
	return (0);
}
