/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:24:45 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:24:45 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "shell.h"
# include <stdio.h>

# define ERR_SHELL "minishell"
# define ERR_QUOTE 1
# define ERR_TOKEN 2
# define ERR_REDIR 6
# define ERR_DIR 7
# define ERR_QUOTE_MSG "cannot interpret unclosed quotes"
# define ERR_TOKEN_MSG "syntax error near unexpected token"
# define ERR_REDIR_MSG "ambiguous redirect"

void	errors(t_shell *shell, char mode, void *param);

#endif
