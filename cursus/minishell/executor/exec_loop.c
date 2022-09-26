/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:55:52 by ademirci          #+#    #+#             */
/*   Updated: 2022/09/25 14:28:44 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	count_proccess(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].is_last != 1 && cmds[i].cmd != NULL)
		i++;
	return (i);
}

void	redirect(t_cmd *cmds)
{
	int	fd;

	fd = 0;
	if (cmds->redir_output != NULL)
	{
		if (cmds->output_type == REDIR_APPEND)
			fd = open(cmds->redir_output, O_CREAT | O_RDWR | O_APPEND, 0777);
		else if (cmds->output_type == REDIR_OUTPUT)
			fd = open(cmds->redir_output, O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(fd, STDOUT_FILENO);
	}
	else
	{
		if (cmds->input_type == REDIR_HEREDOC)
			fd = open(cmds->redir_input, O_CREAT | O_RDWR, 0777);
		else if (cmds->input_type == REDIR_INPUT)
			fd = open(cmds->redir_input, O_CREAT | O_RDWR, 0777);
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
}

void	argv_path(t_cmd *cmd)
{
	int		i;
	char	**argv;

	i = 0;
	while (cmd->argv[i] != NULL)
		i++;
	argv = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (cmd->argv[++i])
	{
		if (i == 0)
			argv[i] = path_returner(cmd->cmd);
		else
			argv[i] = ft_strdup(cmd->argv[i]);
		free(cmd->argv[i]);
		if (cmd->argv[i] == NULL)
			break ;
	}
	argv[i] = NULL;
	cmd->argv = argv;
}
/*
*line 79 and 82 will be deleted after testing
*/

void	exec_func(t_shell *shell, int i, int c_proccess)
{
	if (shell->cmds[i].redir_output != NULL
		|| shell->cmds[i].redir_input != NULL)
		redirect(&(shell->cmds[i]));
	if (i != 0 && shell->cmds[i].wait_ctrl == -1)
		if (dup2(shell->cmds[i - 1].fd[0], STDIN_FILENO) == -1)
			perror("dup2 input");
	if (i != c_proccess - 1 && c_proccess != 1 && !is_wait(shell->cmds[i + 1]))
		if (dup2(shell->cmds[i].fd[1], STDOUT_FILENO) == -1)
			perror("dup2 output");
	if (command_check(shell, i))
	{
		argv_path(&shell->cmds[i]);
		execve(shell->cmds[i].argv[0], shell->cmds[i].argv, NULL);
	}
	exit(1);
}

void	exec_loop(t_shell *shell)
{
	int	c_proccess;
	int	i;

	i = -1;
	c_proccess = count_proccess(shell->cmds);
	while (++i < c_proccess)
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
		if (is_wait(shell->cmds[i + 1]))
			waitpid(shell->cmds[i].pid, &shell->cmds[i].is_sucex, 0);
	}
	wait_list(shell, i);
}
