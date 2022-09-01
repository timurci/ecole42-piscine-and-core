/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:30:07 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/01 16:09:54 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/* extra skip can cause flaws in skip_quote() or split_tokens() */

static char	*skip_quote(char *input)
{
	unsigned char	quote;

	quote = *input;
	input++;
	while (*input && *input != quote)
		input++;
	return (input);
}

static char	*skip_all_quotes(char *input)
{
	input = skip_quote(input);
	if (*input)
		input++;
	if (*input == '\'' || *input == '\"')
		input = skip_all_quotes(input);
	return (input);
}

static int	count_tokens(char *input)
{
	int		count;

	count = 0;
	if (!count && *input)
	{
		count++;
		input++;
	}
	while (*input)
	{
		if (*input == '\"' || *input == '\'')
		{
			if (ft_isspace(*(input - 1)))
				count++;
			input = skip_quote(input);
		}
		else if (ft_isspace(*(input - 1)) && !ft_isspace(*input))
			count++;
		if (*input)
			input++;
	}
	return (count);
}

char	**split_tokens(char *input)
{
	int		itr;
	char	*check_p;
	char	**strs;

	strs = (char **) malloc(sizeof(*strs) * (count_tokens(input) + 1));
	itr = 0;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		check_p = input;
		while (*input && !ft_isspace(*input))
		{
			if (*input == '\"' || *input == '\'')
				input = skip_all_quotes(input);
			else
				while (*input && !ft_isspace(*input)
					&& *input != '\"' && *input != '\'')
					input++;
		}
		strs[itr++] = ft_substr(check_p, 0, input - check_p);
	}
	strs[itr] = NULL;
	return (strs);
}
