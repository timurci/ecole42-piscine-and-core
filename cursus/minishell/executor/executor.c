/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:56:04 by ademirci          #+#    #+#             */
/*   Updated: 2022/09/24 17:58:25 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_mem(t_shell *shell)
{
	tokens_destroy(shell->tokens);
	shell->tokens = NULL;
	cmds_destroy(shell->cmds);
	shell->cmds = NULL;
}

int	executor(char *line, t_shell *shell)
{
	shell->tokens = tokenize(split_tokens(line));
	parse(shell->tokens);
	check_syntax(shell);
	expand(shell);
	parse(shell->tokens);
	rescan_tokens(shell->tokens);
	shell->cmds = split_cmds(shell, shell->tokens);
	exec_loop(shell);
	free_mem(shell);
	return (0);
}
