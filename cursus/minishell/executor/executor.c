/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:56:04 by ademirci          #+#    #+#             */
/*   Updated: 2022/10/04 15:32:30 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_mem(t_shell *shell)
{
	if (shell->tokens)
		tokens_destroy(shell->tokens);
	shell->tokens = NULL;
	if (shell->cmds)
		cmds_destroy(shell->cmds);
	shell->cmds = NULL;
}

static char	found_error(t_shell *shell)
{
	if (shell->raised_error)
	{
		free_mem(shell);
		shell->raised_error = 0;
		return (1);
	}
	return (0);
}

int	executor(char *line, t_shell *shell)
{
	shell->tokens = tokenize(split_tokens(line));
	parse(shell->tokens);
	if (found_error(shell))
		return (1);
	check_syntax(shell);
	if (found_error(shell))
		return (1);
	expand(shell);
	if (found_error(shell))
		return (1);
	parse(shell->tokens);
	shell->cmds = split_cmds(shell, shell->tokens);
	exec_loop(shell);
	free_mem(shell);
	shell->raised_error = 0;
	return (0);
}
