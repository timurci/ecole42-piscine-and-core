/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:20:39 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/05 21:13:16 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"
# include "errors.h"
# include "lexer.h"
# include "libft.h"
# include "signals.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

# define TTYPE_EMPTY -100
# define TTYPE_IGNORE -3
# define TTYPE_CONV -2
# define TTYPE_INIT -1
# define TTYPE_ARG 0
# define TTYPE_ASSIGN 1
# define TTYPE_CMD 2
# define TTYPE_REDIR 3
# define TTYPE_PIPE 4
# define TTYPE_CTRL 5
# define TTYPE_WCARD 6

# define REDIR_INPUT 0
# define REDIR_OUTPUT 1
# define REDIR_HEREDOC 2
# define REDIR_APPEND 3

typedef struct s_scanflag
{
	char	has_cmd;
	char	has_prev_cmd;
	char	has_pipe;
	char	has_prev_pipe;
	char	has_ctrl;
	char	force_ignore;
}	t_scanflag;

void	parse(t_token *tokens);

//executed in parse()
void	rescan_tokens(t_token *tokens);

void	check_syntax(t_shell *shell);
t_cmd	*split_cmds(t_shell *shell, t_token *tokens);
void	heredoc_handler(t_shell *shell, t_cmd *cmd, t_token *token);

/*
 * split_cmds() will run heredoc_handler, which can raise error,
 * hence it is necessary to check if an error has been raised at
 * t_shell.raised_error after executing split_cmds()
 */

#endif
