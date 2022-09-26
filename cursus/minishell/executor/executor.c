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

int	executor(char *line, t_shell *shell)
{
	shell->tokens = tokenize(split_tokens(line));
	parse(shell->tokens);
	expand(shell);
	parse(shell->tokens);
	rescan_tokens(shell->tokens);
	check_syntax(shell);
	shell->cmds = split_cmds(shell, shell->tokens);
	exec_loop(shell);
	return (0);
}
