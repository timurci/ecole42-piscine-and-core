/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:35:24 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/04 15:35:50 by ademirci         ###   ########.fr       */
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
t_shell	*g_shell = NULL;

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
	builtin_sep_assign(shell, "PWD", ft_strdup(shell->cwd));
	if (!lst_find_entry(shell->env_list, "OLDPWD"))
		builtin_sep_assign(shell, "OLDPWD", ft_strdup(shell->cwd));
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	foo(argc, argv);
	g_shell = shell_init(env);
	var_init(g_shell);
	signal(SIGINT, &sig_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline(g_shell->prompt);
		if (!line)
			break ;
		add_history(line);
		g_shell->line = line;
		executor(line, g_shell);
		if (g_shell->line)
			free(line);
		g_shell->line = NULL;
	}
	builtin_exit(g_shell, g_shell);
	return (0);
}
