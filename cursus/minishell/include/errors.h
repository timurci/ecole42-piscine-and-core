/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:24:45 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/04 16:28:02 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "shell.h"
# include <stdio.h>

# define ERR_SHELL "minishell"
# define ERR_QUOTE 1
# define ERR_COLUMN 2
# define ERR_TOKEN 3
# define ERR_ASSIGN 4
# define ERR_REDIR 6
# define ERR_DIR 7
# define ERR_PATH 8
# define ERR_QUOTE_MSG "cannot interpret unclosed quotes"
# define ERR_COLUMN_MSG "cannot interpret columns"
# define ERR_TOKEN_MSG "syntax error near unexpected token"
# define ERR_ASSIGN_MSG "not a valid identifier"
# define ERR_REDIR_MSG "ambiguous redirect"
# define ERR_PATH_MSG "cannot find program"

void	errors(t_shell *shell, char mode, void *param);

#endif
