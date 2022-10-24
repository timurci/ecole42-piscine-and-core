/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:35:20 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/09 14:27:37 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand(t_shell *shell)
{
	t_token	*tokens;
	char	*scan;

	tokens = shell->tokens;
	while (tokens && !shell->raised_error)
	{
		scan = tokens->value;
		while (!shell->raised_error && tokens->type != TTYPE_WCARD && *scan)
		{
			if (*scan == '$' && *(scan + 1) == 0)
				;
			else if (*scan == '$')
				scan = check_var(shell, tokens, scan);
			else if (scan == tokens->value && *scan == '~')
				scan = check_path(tokens, scan);
			else if (*scan == '\"')
				scan = scan_quote(shell, tokens, scan);
			else if (*scan == '\'')
				scan = skip_quote(shell, tokens, scan);
			scan++;
		}
		if (tokens->type == TTYPE_WCARD)
			tokens = handle_wcard(shell, tokens);
		tokens = tokens->next;
	}
}
