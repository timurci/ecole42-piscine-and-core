/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:02:12 by ademirci          #+#    #+#             */
/*   Updated: 2022/10/23 14:50:42 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_wait(t_cmd *cmd)
{
	if (cmd->wait_ctrl == 1 || cmd->wait_ctrl == 0)
		return (1);
	return (0);
}

int	exit_condition(t_shell *shell, int i)
{
	if (i != 0 && !shell->raised_error)
		exit(shell->cmds[i - 1].exit_status);
	exit(EXIT_FAILURE);
}

int	wait_func(t_shell *shell, t_cmd *cmd)
{
	int	exit;

	exit = -1;
	waitpid(cmd->pid, &exit, 0);
	if (!shell->raised_error)
	{
		cmd->exit_status = WEXITSTATUS(exit);
		builtin_sep_assign(shell, "?", ft_itoa(cmd->exit_status));
	}
	return (WEXITSTATUS(exit));
}

void	wait_list(t_shell *shell, int last)
{
	int	i;

	i = -1;
	while (++i < last && shell->cmds)
		wait_func(shell, &shell->cmds[i]);
}
