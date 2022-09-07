/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:33:32 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/07 11:33:33 by tcakmako         ###   ########.fr       */
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
 *  0	str
 *  1 
 *  2	command
 *  3	builtin
 */

typedef struct s_token
{
	char	*value;
	char	type;
}	t_token;

char	**split_tokens(char *input);
t_token	*tokenize(char **cmds);

#endif
