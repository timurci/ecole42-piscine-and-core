/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:34:37 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:19:57 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdlib.h>
# include "shell.h"
# include "errors.h"
# include "parser.h"
# include <sys/types.h>
# include <dirent.h>

void	expand(t_shell *shell);

//utils.c
char	*check_path(t_token *token, char *scan);
char	*check_var(t_shell *shell, t_token *token, char *scan);
char	*scan_quote(t_shell *shell, t_token *token, char *scan);
char	*skip_quote(t_shell *shell, t_token *token, char *scan);

//wildcard_handler.c
t_token	*handle_wcard(t_shell *shell, t_token *tokens);

#endif
