/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:02:12 by ademirci          #+#    #+#             */
/*   Updated: 2022/10/02 22:04:55 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_wait(t_cmd *cmd)
{
	if (cmd->wait_ctrl == 1 || cmd->wait_ctrl == 0)
		return (1);
	return (0);
}

void	wait_func(t_shell *shell, t_cmd *cmd)
{
	int	exit;

	waitpid(cmd->pid, &exit, 0);
	if (!shell->raised_error)
	{
		cmd->exit_status = WEXITSTATUS(exit);
		builtin_sep_assign(shell, "?", ft_itoa(cmd->exit_status));
	}
}

void	wait_list(t_shell *shell, int last)
{
	int	i;

	i = -1;
	while (++i < last && shell->cmds)
		wait_func(shell, &shell->cmds[i]);
}
