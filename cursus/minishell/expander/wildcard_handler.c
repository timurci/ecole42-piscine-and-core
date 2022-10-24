/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:03 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/23 15:31:50 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	is_match(char *wcard, char *filename, int *count_p)
{
	char	last_char;
	char	*scan;

	if (*filename == '.' && *wcard != '.')
		return (0);
	last_char = -1;
	scan = filename;
	while (*wcard)
	{
		while (*wcard == '*')
			last_char = *(wcard++);
		if (!*wcard)
			break ;
		scan = ft_strchr(scan, *wcard);
		if (!scan || (last_char == -1 && filename != scan))
			return (0);
		scan++;
		last_char = *wcard;
		wcard++;
	}
	if (*scan != *wcard && last_char != '*')
		return (0);
	(*count_p)++;
	return (1);
}

static t_token	*clear_and_return(t_token *tks, t_token *n_tks)
{
	if (n_tks)
	{
		clear_and_return(tks, n_tks->next);
		if (n_tks->value)
			free(n_tks->value);
		free(n_tks);
	}
	return (tks);
}

t_token	*insert_wcard(t_shell *shell, t_token *tks, t_token *n_tks, int count)
{
	t_token	*last_p;
	t_token	*prev;

	last_p = n_tks;
	while (last_p->next)
		last_p = last_p->next;
	prev = token_find_offset(shell->tokens, tks, -1);
	if (prev && prev->type == TTYPE_REDIR && count > 1)
	{
		errors(shell, ERR_REDIR, NULL);
		return (clear_and_return(tks, n_tks));
	}
	if (shell->tokens == tks)
	{
		token_destroy(&shell->tokens, tks);
		last_p->next = shell->tokens;
		shell->tokens = n_tks;
	}
	else
	{
		token_destroy(&shell->tokens, tks);
		last_p->next = prev->next;
		prev->next = n_tks;
	}
	return (last_p);
}

t_token	*conv_token(t_token *tkn)
{
	tkn->type = TTYPE_CONV;
	return (tkn);
}

t_token	*handle_wcard(t_shell *shell, t_token *tokens)
{
	DIR				*dir_p;
	struct dirent	*scan_p;
	t_token			*new_tokens;
	int				count;

	dir_p = opendir(shell->cwd);
	if (!dir_p)
	{
		errors(shell, ERR_DIR, (void *) shell->cwd);
		return (tokens);
	}
	scan_p = readdir(dir_p);
	new_tokens = NULL;
	count = 0;
	while (scan_p)
	{
		if (is_match(tokens->value, scan_p->d_name, &count))
			token_append(&new_tokens, ft_strdup(scan_p->d_name), -2);
		scan_p = readdir(dir_p);
	}
	closedir(dir_p);
	if (!count)
		return (conv_token(tokens));
	return (insert_wcard(shell, tokens, new_tokens, count));
}
