/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:51:38 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:06:52 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	is_operator(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TTYPE_PIPE || token->type == TTYPE_CTRL)
		return (1);
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
			&& (tokens->next)->type != TTYPE_EMPTY)
			errors(shell, ERR_TOKEN, (void *) tokens->next->value);
		if (tokens->type == TTYPE_REDIR && !ft_strcmp(tokens->value, ">>")
			&& !tokens->next)
			errors(shell, ERR_TOKEN, (void *) "newline");
		tokens = tokens->next;
	}
}
