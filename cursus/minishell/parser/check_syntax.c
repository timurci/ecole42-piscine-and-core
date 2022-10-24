/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:51:38 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/23 15:00:04 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	check_bracket_complement(t_shell *shell)
{
	t_token	*tokens;
	int		lbracket;
	int		rbracket;

	tokens = shell->tokens;
	lbracket = 0;
	rbracket = 0;
	while (tokens)
	{
		if (tokens->type == TTYPE_LBRACKET)
			lbracket++;
		else if (tokens->type == TTYPE_RBRACKET)
			rbracket++;
		if (rbracket > lbracket)
		{
			errors(shell, ERR_TOKEN, ")");
			return ;
		}
		tokens = tokens->next;
	}
	if (lbracket < rbracket)
		errors(shell, ERR_TOKEN, ")");
	else if (lbracket > rbracket)
		errors(shell, ERR_TOKEN, "(");
}

static char	is_operator(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TTYPE_PIPE || token->type == TTYPE_CTRL)
		return (1);
	return (0);
}

static char	*check_bracket(t_shell *shell, t_token *token)
{
	t_token	*prev;

	prev = token_find_offset(shell->tokens, token, -1);
	if (token->type == TTYPE_LBRACKET
		&& (!token->next || (token->next->type != TTYPE_CMD
				&& token->next->type != TTYPE_LBRACKET)))
	{
		if (token->next)
			return (token->next->value);
		errors(shell, ERR_TOKEN, "newline");
		return (NULL);
	}
	else if (token->type == TTYPE_RBRACKET && prev
		&& prev->type != TTYPE_CMD && prev->type != TTYPE_ARG
		&& prev->type != TTYPE_ASSIGN && prev->type != TTYPE_RBRACKET)
		return (token->next->value);
	else if (token->type == TTYPE_RBRACKET && token->next
		&& token->next->type != TTYPE_PIPE
		&& token->next->type != TTYPE_CTRL
		&& token->next->type != TTYPE_RBRACKET)
		return (token->next->value);
	return (0);
}

void	check_syntax(t_shell *shell)
{
	t_token	*tokens;

	tokens = shell->tokens;
	if (is_operator(tokens))
		errors(shell, ERR_TOKEN, (void *) tokens->value);
	while (tokens && !shell->raised_error)
	{
		if (is_operator(tokens) && is_operator(tokens->next))
			errors(shell, ERR_TOKEN, (void *) tokens->next->value);
		else if (tokens->type == TTYPE_REDIR && tokens->next
			&& (tokens->next)->type != TTYPE_ARG
			&& (tokens->next)->type != TTYPE_WCARD
			&& (tokens->next)->type != TTYPE_EMPTY)
			errors(shell, ERR_TOKEN, (void *) tokens->next->value);
		if (tokens->type == TTYPE_REDIR && !ft_strcmp(tokens->value, ">>")
			&& !tokens->next)
			errors(shell, ERR_TOKEN, (void *) "newline");
		if (*tokens->value != '\'' && *tokens->value != '\"'
			&& ft_strchr(tokens->value, ';'))
			errors(shell, ERR_COLUMN, NULL);
		if (check_bracket(shell, tokens))
			errors(shell, ERR_TOKEN, check_bracket(shell, tokens));
		tokens = tokens->next;
	}
	check_bracket_complement(shell);
}
