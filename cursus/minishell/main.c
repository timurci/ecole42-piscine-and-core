/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:35:24 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/02 17:41:20 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "executor.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>

//global
extern t_shell *shell;

void	foo(int argc, char **argv)
{
	argc = 0;
	argv = NULL;
	if (argc || argv)
		return ;
}

static void	var_init(t_shell *shell)
{
	builtin_sep_assign(shell, "?", ft_strdup("0"));
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	//sil
	foo(argc, argv);
	//sil
	shell = shell_init(env);
	var_init(shell);
	signal(SIGINT, &sig_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline(shell->prompt);
		if (!line)
			break ;
		add_history(line);
		shell->line = line;
		executor(line, shell);
		if (shell->line)
			free(line);
		shell->line = NULL;
	}
	builtin_exit(shell, shell);
	return (0);
}
