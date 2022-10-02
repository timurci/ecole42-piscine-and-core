/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:51:46 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:23:13 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_env(char **env)
{
	char	**scan;

	scan = env;
	while (*scan)
		free(*(scan++));
	free(env);
}

void	cmds_destroy(t_cmd *cmds)
{
	int	itr;

	if (!cmds)
		return ;
	itr = 0;
	while (!cmds[itr].is_last)
	{
		if (cmds[itr].env)
			free_env(cmds[itr].env);
		if (cmds[itr].argv)
			free(cmds[itr].argv);
		if (cmds[itr].cmd_replaced)
			free(cmds[itr].cmd);
		if (cmds[itr].input_type == REDIR_HEREDOC)
		{
			unlink(cmds[itr].redir_input);
			free(cmds[itr].redir_input);
		}
		itr++;
	}
	free(cmds);
}
