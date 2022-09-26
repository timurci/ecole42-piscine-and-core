/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:27:07 by ademirci          #+#    #+#             */
/*   Updated: 2022/09/24 20:27:20 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "libft.h"
# include "shell.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

//path_returner.c
char	*path_returner(char *cmd);

//executor.c
int		executor(char *line, t_shell *shell);

//exec_loop.c
void	exec_loop(t_shell *shell);

//utils.c
int		is_wait(t_cmd cmd);
void	wait_list(t_shell *shell, int last);
int		count_proccess(t_cmd *cmds);
int		command_check(t_shell *shell, int i);
int		error_check(t_shell *shell, int i);
#endif
