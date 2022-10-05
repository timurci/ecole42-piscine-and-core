/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:41:39 by ademirci          #+#    #+#             */
/*   Updated: 2022/10/04 16:37:21 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo") || !ft_strcmp(cmd->cmd, "cd")
		|| !ft_strcmp(cmd->cmd, "env") || !ft_strcmp(cmd->cmd, "export")
		|| !ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "unset")
		|| !ft_strcmp(cmd->cmd, "exit"))
		return (1);
	return (0);
}

int	is_assignment(t_cmd *cmd)
{
	if (cmd->cmd == NULL && cmd->argv != NULL)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (builtin_cd(shell, cmd->argv, NULL));
	else if (!ft_strcmp(cmd->cmd, "echo"))
		return (builtin_echo(cmd->argv));
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		return (builtin_pwd(shell));
	else if (!ft_strcmp(cmd->cmd, "env"))
		return (builtin_env(shell));
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (builtin_export(shell, cmd->argv, NULL));
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (builtin_unset(shell, cmd->argv));
	else if (!ft_strcmp(cmd->cmd, "exit"))
		return (builtin_exit(shell, NULL));
	return (0);
}
