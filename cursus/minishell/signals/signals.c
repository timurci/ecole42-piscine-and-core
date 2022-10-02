#include "shell.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
t_shell	*shell;

static void	kill_all(t_cmd *cmds, int i)
{
	int	j;

	j = -1;
	while (++j <= i)
	{
		kill(cmds[i].pid, SIGTERM);
	}
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
	if (shell->cmds && has_child(shell->cmds, &current_child))
	{
		kill_all(shell->cmds, current_child);
		is_redisplay = 1;
		free_mem(shell);
	}
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (is_redisplay == 0)
		rl_redisplay();
}

