/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:33:55 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/07 11:33:56 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "lexer.h"

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}	t_dict;

typedef struct s_shell
{
	char	*prompt;
	char	*cwd;
	t_token	*tokens;
	t_dict	*var_list;
	t_dict	*env_list;
}	t_shell;

t_shell	*shell_init(t_dict *exp_list);

char	*get_prompt(t_shell *shell);

#endif
