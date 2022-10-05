/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:24:33 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/04 16:39:39 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdbool.h>

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

static void	handle_error(t_shell *shell, void *to_free, char *expr, void *param)
{
	if (to_free)
		free(to_free);
	if (param)
		errors(shell, ERR_ASSIGN, expr);
	shell->raised_error = 1;
}

static void	export_with_assign(t_shell *shell, char *expr, void *param)
{
	t_dict	*entry;
	char	*key;
	char	*value;

	key = assignment_key_dup(expr);
	if (key && !ft_strcmp(key, ""))
	{
		handle_error(shell, key, expr, param);
		return ;
	}
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

int	builtin_export(t_shell *shell, char **argv, void *param)
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
			export_with_assign(shell, *argv, param);
		else
			export_wout_assign(shell, *argv);
		if (shell->raised_error)
			return (1);
		argv++;
	}
	return (0);
}
