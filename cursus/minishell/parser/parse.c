/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:20:44 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 11:52:53 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	is_assignment(t_token *itr)
{
	if (itr->type == TTYPE_CONV)
		return (0);
	if (!ft_strchr(itr->value, '='))
		return (0);
	return (1);
}

static char	is_command(t_token *tokens, t_token *itr)
{
	t_token	*prev;

	if (tokens == itr)
		return (1);
	prev = token_find_offset(tokens, itr, -1);
	if (itr->type != TTYPE_ASSIGN
		&& (prev->type == TTYPE_PIPE || prev->type == TTYPE_CTRL))
		return (1);
	if (prev->type == TTYPE_ASSIGN)
		return (1);
	return (0);
}

static char	is_redirection(t_token *itr)
{
	char	*val;

	if (itr->type == TTYPE_CONV)
		return (0);
	val = itr->value;
	if (!ft_strcmp(val, "<") || !ft_strcmp(val, ">")
		|| !ft_strcmp(val, "<<") || !ft_strcmp(val, ">>"))
		return (1);
	return (0);
}

static char	is_ctrl(t_token *itr)
{
	char	*val;

	if (itr->type == TTYPE_CONV)
		return (0);
	val = itr->value;
	if (!ft_strcmp(val, "&&") || !ft_strcmp(val, "||"))
		return (1);
	return (0);
}

void	parse(t_token *tokens)
{
	t_token	*itr;

	itr = tokens;
	while (itr)
	{
		if (is_assignment(itr))
			itr->type = TTYPE_ASSIGN;
		else if (is_redirection(itr))
			itr->type = TTYPE_REDIR;
		else if (itr->type != TTYPE_CONV && !ft_strcmp(itr->value, "|"))
			itr->type = TTYPE_PIPE;
		else if (is_ctrl(itr))
			itr->type = TTYPE_CTRL;
		else if (itr->type != TTYPE_CONV && ft_strchr(itr->value, '*'))
			itr->type = TTYPE_WCARD;
		else if (is_command(tokens, itr))
			itr->type = TTYPE_CMD;
		else
			itr->type = TTYPE_ARG;
		itr = itr->next;
	}
	rescan_tokens(tokens);
}
