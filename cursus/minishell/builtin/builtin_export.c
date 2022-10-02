/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:24:33 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/02 17:24:36 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_info(t_shell *shell)
{
	t_dict	*env;

	env = shell->env_list;
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

static void	export_with_assign(t_shell *shell, char *expr)
{
	t_dict	*entry;
	char	*key;
	char	*value;

	key = assignment_key_dup(expr);
	value = assignment_val_dup(expr);
	entry = lst_find_entry(shell->var_list, key);
	if (entry)
		lst_destroy_entry(&shell->var_list, key);
	entry = lst_find_entry(shell->env_list, key);
	if (entry)
	{
		free(key);
		if (entry->value)
			free(entry->value);
		entry->value = value;
	}
	else
		lst_add_back(&shell->env_list, key, value);
}

static void	export_wout_assign(t_shell *shell, char *expr)
{
	t_dict	*entry;
	char	*key;
	char	*value;

	entry = lst_find_entry(shell->env_list, expr);
	if (entry)
		return ;
	entry = lst_find_entry(shell->var_list, expr);
	if (entry)
	{
		key = ft_strdup(expr);
		value = ft_strdup(entry->value);
		lst_destroy_entry(&shell->var_list, expr);
		lst_add_back(&shell->env_list, key, value);
	}
}

int	builtin_export(t_shell *shell, char **argv)
{
	char	*assign;

	if (!argv)
		return (1);
	argv++;
	if (!*argv)
		print_info(shell);
	while (*argv)
	{
		assign = ft_strchr(*argv, '=');
		if (assign)
			export_with_assign(shell, *argv);
		else
			export_wout_assign(shell, *argv);
		argv++;
	}
	return (0);
}
