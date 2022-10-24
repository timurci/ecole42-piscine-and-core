/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:04:39 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/23 15:04:43 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*check_brackets(t_cmd *cmds, t_cmd *cmd, t_token *token)
{
	static int		bracket_degree = 0;
	static t_cmd	*last_cmds = NULL;
	t_token			*scan;

	if (last_cmds != cmds)
	{
		last_cmds = cmds;
		bracket_degree = 0;
	}
	scan = token;
	cmd->in_bracket = bracket_degree;
	while (scan && scan->type != TTYPE_CTRL && scan->type != TTYPE_PIPE)
	{
		if (scan->type == TTYPE_LBRACKET)
			cmd->in_bracket = ++bracket_degree;
		if (scan->type == TTYPE_RBRACKET)
			bracket_degree--;
		scan = scan->next;
	}
	while (token && token->type == TTYPE_LBRACKET)
		token = token->next;
	return (token);
}

char	is_cmd_end(t_token *token)
{
	if (token->type != TTYPE_PIPE && token->type != TTYPE_CTRL
		&& token->type != TTYPE_RBRACKET)
		return (0);
	return (1);
}
