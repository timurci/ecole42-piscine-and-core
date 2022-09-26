/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:34:29 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:31:10 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "lexer.h"
#include "expander.h"
#include "parser.h"

void	print_tokens(t_token *tokens)
{
	printf("%-20s\t%s\n", "[VALUE]", "[TYPE_NUM]");
	while (tokens)
	{
		printf("%-20s\t% 5d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

void	print_all_cmds(t_cmd *cmds)
{
	int	itr;

	while (!cmds->is_last)
	{
		printf("----------\n");
		printf("%-10s: %s\n", "command", cmds->cmd);
		if (cmds->argv)
			printf("%-10s:\n", "args");
		itr = 0;
		while (cmds->argv && cmds->argv[itr])
			printf("%11s %s\n", "*", cmds->argv[itr++]);
		if (cmds->redir_input)
			printf("%-10s: %s\n", "redir_in", cmds->redir_input);
		if (cmds->redir_output)
			printf("%-10s: %s\n", "redir_out", cmds->redir_output);
		printf("%-10s: %d\n", "wait_ctrl", cmds->wait_ctrl);
		printf("----------\n");
		cmds++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	t_cmd	*cmds;

	if (ac != 2 || !av)
		return (1);
	shell = shell_init(env);
	//shell->tokens = tokenize(split_tokens("x=>file2 ~/Desktop '$USER' $SHELL \"$USER\""));
	shell->tokens = tokenize(split_tokens("x=a y=b export z=c && export k=m"));
	print_tokens(shell->tokens);
	printf("--------\n");
	parse(shell->tokens);
	expand(shell);
	parse(shell->tokens);
	rescan_tokens(shell->tokens);
	print_tokens(shell->tokens);
	check_syntax(shell);
	cmds = split_cmds(shell, shell->tokens);
	shell->cmds = cmds;
	print_all_cmds(cmds);
	cmds_destroy(cmds);
	shell->cmds = NULL;
	shell_destroy(shell);
	return (0);
}
