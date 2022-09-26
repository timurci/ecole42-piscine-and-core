/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:33:32 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:19:28 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "libft.h"

/*
 * -100	empty / null
 * -2	converted
 * -1	initial
 *  0	argument
 *  1	assignment
 *  2	command
 *  3	redirection
 *  4	pipe
 */

typedef struct s_token
{
	char			*value;
	char			type;
	struct s_token	*next;
}	t_token;

//lexer.c
char	**split_tokens(char *input);

//tokenizer.c
t_token	*tokenize(char **cmds);

//utils.c
void	token_append(t_token **token_pp, char *value, char type);
t_token	*token_insert(t_token **token_pp, t_token *dst, char *value, char type);
t_token	*token_find_offset(t_token *tokens, t_token *target, int offset);
void	token_destroy(t_token **token_pp, t_token *target);

#endif
