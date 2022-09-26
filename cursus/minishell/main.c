/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:35:24 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 19:55:07 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "executor.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	foo(int argc, char **argv)
{
	argc = 0;
	argv = NULL;
	if (argc || argv)
		return ;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	char	*line;

	//sil
	foo(argc, argv);
	//sil
	shell = shell_init(env);
	while (1)
	{
		line = readline(shell->prompt);
		if (!line)
			return (1);
		add_history(line);
		executor(line, shell);
		free(line);
	}
	return (0);
}
