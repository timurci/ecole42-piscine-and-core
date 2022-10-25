/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:55:52 by ademirci          #+#    #+#             */
/*   Updated: 2022/10/25 11:22:33 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	count_proccess(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].is_last != 1)
		i++;
	return (i);
}

void	redirect(t_cmd *cmds)
{
	int	fd;

	fd = 0;
	if (cmds->redir_output)
	{
		if (cmds->output_type == REDIR_APPEND)
			fd = open(cmds->redir_output, O_CREAT | O_RDWR | O_APPEND, 0777);
		else if (cmds->output_type == REDIR_OUTPUT)
			fd = open(cmds->redir_output, O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (cmds->redir_input)
	{
		if (cmds->input_type == REDIR_HEREDOC)
			fd = open(cmds->redir_input, O_CREAT | O_RDWR, 0777);
		else if (cmds->input_type == REDIR_INPUT)
			fd = open(cmds->redir_input, O_CREAT | O_RDWR, 0777);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	argv_path(t_shell *shell, t_cmd *cmd)
{
	cmd->cmd = path_returner(shell, cmd->cmd);
	if (!cmd->cmd)
	{
		errors(shell, ERR_PATH, cmd->argv[0]);
		return ;
	}
	cmd->cmd_replaced = 1;
	cmd->env = list_to_env(shell->env_list);
}
/*
*line 79 and 82 will be deleted after testing
*/

void	exec_func(t_shell *shell, int i, int c_proccess)
{
	if (i != 0 && shell->cmds[i].wait_ctrl == -1)
		dup2(shell->cmds[i - 1].fd[0], STDIN_FILENO);
	if (i != c_proccess - 1 && c_proccess != 1 && !is_wait(&shell->cmds[i + 1]))
		dup2(shell->cmds[i].fd[1], STDOUT_FILENO);
	if (shell->cmds[i].redir_output || shell->cmds[i].redir_input)
		redirect(&(shell->cmds[i]));
	if (command_check(shell, i))
	{
		if (is_builtin(&shell->cmds[i]))
		{
			if (exec_builtin(shell, &shell->cmds[i]))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		if (is_assignment(&shell->cmds[i]))
		{
			if (builtin_assign(shell, shell->cmds[i].argv))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		argv_path(shell, &shell->cmds[i]);
		if (!shell->raised_error)
			execve(shell->cmds[i].cmd, shell->cmds[i].argv, shell->cmds[i].env);
	}
	exit_condition(shell, i);
}

void	exec_loop(t_shell *shell)
{
	int	c_proccess;
	int	i;

	i = -1;
	c_proccess = count_proccess(shell->cmds);
	while (++i < c_proccess && !shell->raised_error)
	{
		if (c_proccess != 1 && i != c_proccess - 1)
			pipe(shell->cmds[i].fd);
		shell->cmds[i].pid = fork();
		if (shell->cmds[i].pid == 0)
			exec_func(shell, i, c_proccess);
		if (i != 0)
			close(shell->cmds[i - 1].fd[0]);
		if (i != c_proccess - 1)
			close(shell->cmds[i].fd[1]);
		if (is_wait(&shell->cmds[i + 1]))
			wait_func(shell, &shell->cmds[i]);
		builtin_main_update(shell, i, c_proccess);
	}
	wait_list(shell, i);
}
