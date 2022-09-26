/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:57 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/24 18:08:44 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*combine_and_free(char *s1, char *s2, char *s3)
{
	char	*news;

	news = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	s2 = news;
	news = ft_strjoin(s2, s3);
	free(s2);
	free(s3);
	return (news);
}

char	*check_path(t_token *token, char *scan)
{
	char	*news;
	char	*home;

	home = getenv("HOME");
	news = ft_strjoin(home, scan + 1);
	free(token->value);
	token->value = news;
	return (token->value + ft_strlen(home) - 1);
}

char	*check_var(t_shell *shell, t_token *token, char *scan)
{
	char	*check_p;
	char	*tmp;
	char	*replace;
	char	*hanger;
	size_t	hanger_size;

	check_p = scan++;
	while (*scan && *scan != '\"' && *scan != '\''
		&& !ft_isspace(*scan))
		scan++;
	tmp = ft_substr(check_p, 1, scan - check_p - 1);
	replace = ft_strdup(lst_find_value(shell->var_list, tmp));
	if (!replace)
		replace = ft_strdup(lst_find_value(shell->env_list, tmp));
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

char	*scan_quote(t_shell *shell, t_token *token, char *scan)
{
	char	*check_p;
	size_t	hanger_size;

	check_p = scan++;
	while (*scan && *scan != '\"')
	{
		if (*scan == '$')
		{
			scan = check_var(shell, token, scan);
			check_p = token->value;
		}
		scan++;
	}
	if (*scan != '\"')
	{
		errors(shell, ERR_QUOTE, NULL);
		return (NULL);
	}
	*check_p = 0;
	*scan = 0;
	hanger_size = ft_strlen(scan + 1);
	token->value = combine_and_free(token->value,
			ft_strdup(check_p + 1), ft_strdup(scan + 1));
	token->type = -2;
	return (ft_strrchr(token->value, 0) - hanger_size - 1);
}

char	*skip_quote(t_shell *shell, t_token *token, char *scan)
{
	char	*check_p;
	size_t	hanger_size;

	check_p = scan++;
	while (*scan && *scan != '\'')
		scan++;
	if (*scan != '\'')
	{
		errors(shell, ERR_QUOTE, NULL);
		return (NULL);
	}
	*check_p = 0;
	*scan = 0;
	hanger_size = ft_strlen(scan + 1);
	token->value = combine_and_free(token->value,
			ft_strdup(check_p + 1), ft_strdup(scan + 1));
	token->type = -2;
	return (ft_strrchr(token->value, 0) - hanger_size - 1);
}
