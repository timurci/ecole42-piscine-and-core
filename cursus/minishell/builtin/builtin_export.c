#include "builtins.h"

static void	export_with_assign(t_shell *shell, char *expr)
{
	t_dict	*entry;
	char	*key;

	key = assignment_key_dup(expr);
	entry = lst_find_entry(shell->var_list, key);
	if (entry)
		lst_destroy_entry(&shell->var_list, key);
	free(key);
	builtin_single_assign(shell, expr);
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
		return (0);
	argv++;
	while (*argv)
	{
		assign = ft_strchr(*argv, '=');
		if (assign)
			export_with_assign(shell, *argv);
		else
			export_wout_assign(shell, *argv);
		argv++;
	}
}
