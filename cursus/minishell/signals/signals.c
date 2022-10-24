/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:40:42 by ademirci          #+#    #+#             */
/*   Updated: 2022/10/23 15:01:55 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

extern t_shell	*g_shell;

static void	kill_all(t_cmd *cmds, int i)
{
	int	j;

	j = -1;
	while (++j <= i)
		kill(cmds[i].pid, SIGTERM);
}

static int	has_child(t_cmd *cmds, int *current_child)
{
	int	i;

	i = -1;
	while (cmds[++i].is_last != 1)
	{
		if (cmds[i].exit_status == -1)
		{
			*current_child = i;
			return (1);
		}
	}
	return (0);
}

static void	free_mem(t_shell *shell)
{
	cmds_destroy(shell->cmds);
	shell->cmds = NULL;
	if (shell->tokens)
		tokens_destroy(shell->tokens);
	shell->tokens = NULL;
	if (shell->line)
		free(shell->line);
	shell->line = NULL;
}

void	sig_ctrlc(int sig)
{
	int		current_child;
	char	is_redisplay;

	(void)sig;
	current_child = 0;
	is_redisplay = 0;
	if (g_shell->cmds && has_child(g_shell->cmds, &current_child))
	{
		kill_all(g_shell->cmds, current_child);
		is_redisplay = 1;
		free_mem(g_shell);
		g_shell->raised_error = 1;
	}
	if (g_shell->doc_open)
	{
		if (!g_shell->child_pid)
			exit(EXIT_SUCCESS);
		g_shell->raised_error = 1;
	}
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (is_redisplay == 0 && !g_shell->doc_open)
		rl_redisplay();
}
