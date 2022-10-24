/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:20:44 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/23 15:24:09 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	type_to_bracket(t_token *itr, char check)
{
	if (check)
	{
		if (itr->type != TTYPE_CONV
			&& (!ft_strcmp(itr->value, "(") || !ft_strcmp(itr->value, ")")))
			return (1);
		return (0);
	}
	if (*itr->value == '(')
		itr->type = TTYPE_LBRACKET;
	else
		itr->type = TTYPE_RBRACKET;
	return (0);
}

static char	is_command(t_token *tokens, t_token *itr)
{
	t_token	*prev;
	t_token	*prev2;

	if (tokens == itr && ft_strlen(itr->value))
		return (1);
	prev = token_find_offset(tokens, itr, -1);
	prev2 = token_find_offset(tokens, itr, -2);
	if (itr->type != TTYPE_ASSIGN && ft_strlen(itr->value)
		&& (prev->type == TTYPE_PIPE || prev->type == TTYPE_CTRL
			|| (prev2 && prev2->type == TTYPE_REDIR)))
		return (1);
	if (prev && prev->type == TTYPE_ASSIGN)
		return (1);
	if (prev
		&& (prev->type == TTYPE_LBRACKET || prev->type == TTYPE_RBRACKET))
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

static char	is_wcard(t_token *tokens, t_token *itr)
{
	t_token	*prev;

	prev = token_find_offset(tokens, itr, -1);
	if (ft_strchr(itr->value, '\"') || ft_strchr(itr->value, '\''))
		return (0);
	if (ft_strchr(itr->value, '*'))
	{
		if (itr->type != TTYPE_CONV
			&& !(prev && prev->type == TTYPE_REDIR
				&& !ft_strcmp(prev->value, "<<")))
			return (1);
	}
	return (0);
}

void	parse(t_token *tokens)
{
	t_token	*itr;

	itr = tokens;
	while (itr)
	{
		if (itr->type != TTYPE_CONV && ft_strchr(itr->value, '='))
			itr->type = TTYPE_ASSIGN;
		else if (type_to_bracket(itr, 1))
			type_to_bracket(itr, 0);
		else if (is_redirection(itr))
			itr->type = TTYPE_REDIR;
		else if (itr->type != TTYPE_CONV && !ft_strcmp(itr->value, "|"))
			itr->type = TTYPE_PIPE;
		else if (itr->type != TTYPE_CONV
			&& (!ft_strcmp(itr->value, "&&") || !ft_strcmp(itr->value, "||")))
			itr->type = TTYPE_CTRL;
		else if (is_wcard(tokens, itr))
			itr->type = TTYPE_WCARD;
		else if (is_command(tokens, itr))
			itr->type = TTYPE_CMD;
		else
			itr->type = TTYPE_ARG;
		itr = itr->next;
	}
	rescan_tokens(tokens);
}
