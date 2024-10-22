/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:24:56 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/02 17:24:58 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	env_destroy(char **env)
{
	char	**scan;

	if (!env)
		return ;
	scan = env;
	while (*scan)
		free(*(scan++));
	free(env);
}

static void	print_per_line(char **env)
{
	if (!env)
		return ;
	while (*env)
		printf("%s\n", *(env++));
}

int	builtin_env(t_shell *shell)
{
	char	**env;

	env = list_to_env(shell->env_list);
	if (!env)
		return (1);
	print_per_line(env);
	env_destroy(env);
	return (0);
}
