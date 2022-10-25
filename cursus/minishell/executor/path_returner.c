/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_returner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:56:14 by ademirci          #+#    #+#             */
/*   Updated: 2022/10/25 11:28:19 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_all(char **spath, char *new_cmd)
{
	int	i;

	i = -1;
	while (spath[++i] != NULL)
		free(spath[i]);
	free(spath);
	free(new_cmd);
}
//access_perm line 31 and line 32 error

int	access_perm(char *cmd)
{
	int	r;

	r = 0;
	r += access(cmd, F_OK);
	r += access(cmd, R_OK);
	if (r == 0)
		return (1);
	return (0);
}

char	*path_returner(t_shell *shell, char *cmd)
{
	int		i;
	char	**spath;
	char	*apath;
	char	*new_cmd;

	if (access_perm(cmd))
		return (ft_strdup(cmd));
	new_cmd = ft_strjoin("/", cmd);
	spath = ft_split(lst_find_value(shell->env_list, "PATH"), ':');
	if (!spath)
		return (NULL);
	i = -1;
	while (spath[++i])
	{
		apath = ft_strjoin(spath[i], new_cmd);
		if (access_perm(apath))
		{
			free_all(spath, new_cmd);
			return (apath);
		}
		free (apath);
	}
	free_all(spath, new_cmd);
	return (NULL);
}
