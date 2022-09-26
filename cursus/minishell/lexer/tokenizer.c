/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:34:06 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:24:35 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*tokenize(char **cmds)
{
	size_t	itr;
	t_token	*tokens;

	itr = 0;
	tokens = NULL;
	while (cmds[itr])
		token_append(&tokens, cmds[itr++], -1);
	free(cmds);
	return (tokens);
}
