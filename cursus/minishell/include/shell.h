/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:33:55 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/09 17:51:27 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "lexer.h"

typedef struct s_cmd
{
	int		fd[2];
	int		pid;
	char	**env;
	char	*cmd;
	char	cmd_replaced;
	char	**argv;
	char	*redir_input;
	char	input_type;
	char	*redir_output;
	char	output_type;
	char	exit_status;
	char	wait_ctrl;
	char	in_bracket;
	char	is_last;
}	t_cmd;

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}	t_dict;

typedef struct s_shell
{
	char	*prompt;
	char	*line;
	char	*cwd;
	t_token	*tokens;
	t_dict	*var_list;
	t_dict	*env_list;
	t_cmd	*cmds;
	char	raised_error;
	char	doc_open;
	int		child_pid;
}	t_shell;

char	*get_prompt(t_shell *shell);
t_shell	*shell_init(char **evn);
void	shell_destroy(t_shell *shell);
void	tokens_destroy(t_token *tokens);
void	cmds_destroy(t_cmd *cmds);

//env_convert.c
t_dict	*env_to_list(char **env);
char	**list_to_env(t_dict *lst);

//utils.c
void	lst_add_front(t_dict **list, char *key, char *value);
void	lst_add_back(t_dict **list, char *key, char *value);
t_dict	*lst_find_entry(t_dict *list, char *key);
char	*lst_find_value(t_dict *list, char *key);
void	lst_destroy_entry(t_dict **list, char *key);

#endif
