/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:24:49 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/04 15:36:54 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_env(t_shell *shell, char *oldpwd, char *newpwd)
{
	char	*n_oldpwd;
	char	*n_newpwd;
	t_dict	*entry;

	n_oldpwd = ft_strdup(oldpwd);
	n_newpwd = ft_strdup(newpwd);
	entry = lst_find_entry(shell->env_list, "PWD");
	if (!entry)
		lst_add_back(&shell->env_list, ft_strdup("PWD"), n_newpwd);
	else
		builtin_sep_assign(shell, "PWD", n_newpwd);
	entry = lst_find_entry(shell->env_list, "OLDPWD");
	if (!entry)
		lst_add_back(&shell->env_list, ft_strdup("OLDPWD"), n_oldpwd);
	else
		builtin_sep_assign(shell, "OLDPWD", n_oldpwd);
}

static int	extend_chdir(t_shell *shell, char *path, void *param)
{
	if (chdir(path))
	{
		if (param)
			errors(shell, ERR_DIR, (void *) path);
		shell->raised_error = 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(t_shell *shell, char **argv, void *param)
{
	char	*oldpwd;

	argv++;
	if (*argv && ft_strlen(*argv) == 1 && **argv == '-'
		&& !extend_chdir(shell,
			lst_find_value(shell->env_list, "OLDPWD"), param))
		;
	else if (*argv && extend_chdir(shell, *argv, param))
		return (1);
	else if (!*argv && extend_chdir(shell, getenv("HOME"), param))
		return (1);
	oldpwd = shell->cwd;
	shell->cwd = getcwd(NULL, 0);
	update_env(shell, oldpwd, shell->cwd);
	if (shell->prompt)
		free(shell->prompt);
	shell->prompt = get_prompt(shell);
	if (oldpwd)
		free(oldpwd);
	return (0);
}
