/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:35:24 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/07 11:35:25 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	print_env(char **env)
{
	while (*env)
		printf("%s\n", *(env++));
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	char	*line;

	//sil
	if (argc == 1)
		argv = NULL;
	//sil
	shell = shell_init(NULL);
	print_env(env);
	while (1)
	{
		line = readline(shell->prompt);
		if (!line)
			return (1);
		add_history(line);
		//execute(line);
		if (ft_strcmp(line, "exit"))
			printf("%s\n", line); //remove this line after implementing execute()
		else
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (0);
}
