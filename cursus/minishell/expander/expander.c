/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:35:20 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/07 12:33:59 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*combine_and_free(char *s1, char *s2, char *s3)
{
	char	*news;

	news = ft_strjoin(s1, s2);
	free(s2);
	news = ft_strjoin(news, s3);
	free(s3);
	return (news);
}

static char	*check_var(/*t_shell *shell, */t_token *token, char *scan)
{
	char	*check_p;
	char	*tmp;
	char	*replace;
	char	*hanger;
	size_t	hanger_size;

	check_p = scan++;
	if (!*scan)
		return (check_p);
	while (*scan && *scan != '\"' && *scan != '\''
			&& !ft_isspace(*scan))
		scan++;
	tmp = ft_substr(check_p, 1, scan - check_p - 1);
	replace = /*find_token(shell->var_list, tmp)*/ NULL;
	if (!replace)
		replace = /*find_token(shell->env_list, tmp)*/ NULL;
	free(tmp);
	if (!replace)
		replace = ft_strdup("");
	hanger = ft_strdup(scan);
	*check_p = 0;
	hanger_size = ft_strlen(hanger);
	token->value = combine_and_free(token->value, replace, hanger);
	token->type = -2;
	return (ft_strrchr(token->value, 0) - hanger_size - 1);
}

static char	*scan_quote(/*t_shell *shell, */t_token *token, char *scan)
{
	char	*check_p;
	size_t	hanger_size;
	
	check_p = scan;
	while (*scan && *scan != '\"')
	{
		if (*scan == '$')
			scan = check_var(token, scan);
		scan++;
	}
	if (*scan != '\"')
		;//error(shell, 1/*mode quote_not_found/syntax error*/);
	*check_p = 0;
	hanger_size = ft_strlen(scan + 1);
	token->value = combine_and_free(token->value,
			ft_strdup(check_p + 1), ft_strdup(scan + 1));
	return (ft_strrchr(token->value, 0) - hanger_size - 1);
}

static char	*skip_quote(/*t_shell *shell, */t_token *token, char *scan)
{
	char	*check_p;
	size_t	hanger_size;

	check_p = scan++;
	while (*scan && *scan != '\'')
		scan++;
	if (*scan != '\'')
		;//error(shell, 1/*mode quote_not_found/syntax error*/);
	*check_p = 0;
	hanger_size = ft_strlen(scan + 1);
	token->value = combine_and_free(token->value,
			ft_strdup(check_p + 1), ft_strdup(scan + 1));
	return (ft_strrchr(token->value, 0) - hanger_size - 1);
}

void	expand(t_shell *shell)
{
	t_token	*tokens;
	char	*scan;

	tokens = shell->tokens;
	while (tokens->type != -100)
	{
		scan = tokens->value;
		while (*scan)
		{
			if (*scan == '$')
				scan = check_var(/*shell, */tokens, scan);
			else if (*scan == '\"')
				scan = scan_quote(/*shell, */tokens, scan);
			else if (*scan == '\'')
				scan = skip_quote(/*shell, */tokens, scan);
			scan++;
		}
		tokens++;
	}
}
