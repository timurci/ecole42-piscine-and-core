/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:24:03 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/02 17:24:06 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*assignment_key_dup(char *expr)
{
	char	*assign;
	char	*key;

	if (!expr)
		return (NULL);
	assign = ft_strchr(expr, '=');
	if (!assign)
		return (NULL);
	*assign = 0;
	key = ft_strdup(expr);
	*assign = '=';
	return (key);
}

char	*assignment_val_dup(char *expr)
{
	char	*assign;
	char	*value;

	if (!expr)
		return (NULL);
	assign = ft_strchr(expr, '=');
	if (!assign)
		return (NULL);
	value = ft_strdup(assign + 1);
	return (value);
}

int	builtin_assign(t_shell *shell, char **argv)
{
	t_dict	*entry;
	char	*key;
	char	*value;

	while (*argv)
	{
		key = assignment_key_dup(*argv);
		value = assignment_val_dup(*argv);
		entry = lst_find_entry(shell->env_list, key);
		if (!entry)
			entry = lst_find_entry(shell->var_list, key);
		if (entry)
		{
			free(key);
			if (entry->value)
				free(entry->value);
			entry->value = value;
		}
		else
			lst_add_back(&shell->var_list, key, value);
		argv++;
	}
	return (0);
}

int	builtin_single_assign(t_shell *shell, char *expr)
{
	t_dict	*entry;
	char	*key;
	char	*value;

	key = assignment_key_dup(expr);
	value = assignment_val_dup(expr);
	entry = lst_find_entry(shell->env_list, key);
	if (!entry)
		entry = lst_find_entry(shell->var_list, key);
	if (entry)
	{
		free(key);
		if (entry->value)
			free(entry->value);
		entry->value = value;
	}
	else
		lst_add_back(&shell->var_list, key, value);
	return (0);
}

//the key will not be free, but the value will be freed.
int	builtin_sep_assign(t_shell *shell, char *key, char *value)
{
	char	*expr;
	char	*head;
	int		ret_val;

	head = ft_strjoin(key, "=");
	expr = ft_strjoin(head, value);
	free(head);
	if (value)		//updated
		free(value);
	ret_val = builtin_single_assign(shell, expr);
	free(expr);
	return (ret_val);
}
