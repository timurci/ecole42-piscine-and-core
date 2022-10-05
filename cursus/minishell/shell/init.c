/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:34:18 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/03 18:30:25 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_prompt(t_shell *shell)
{
	char	*latter_dir;
	char	*prompt;

	if (!shell->cwd)
		shell->cwd = getcwd(NULL, 0);
	latter_dir = ft_strrchr(shell->cwd, '/');
	if (!latter_dir)
		return (ft_strdup("minishell > "));
	if (ft_strlen(latter_dir) == 1)
		return (ft_strdup("minishell / > "));
	else
	{
		if (ft_strcmp(shell->cwd, getenv("HOME")))
			latter_dir = ft_strjoin(latter_dir + 1, " > ");
		else
			latter_dir = ft_strjoin("~", " > ");
		prompt = ft_strjoin("minishell ", latter_dir);
		free(latter_dir);
		return (prompt);
	}
}

t_shell	*shell_init(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(*shell));
	if (!shell)
		return (NULL);
	shell->cwd = getcwd(NULL, 0);
	shell->prompt = get_prompt(shell);
	shell->tokens = NULL;
	shell->var_list = NULL;
	shell->env_list = NULL;
	shell->cmds = NULL;
	shell->line = NULL;
	shell->raised_error = 0;
	shell->child_pid = -1;
	if (env)
		shell->env_list = env_to_list(env);
	return (shell);
}

void	tokens_destroy(t_token *tokens)
{
	if (tokens)
	{
		tokens_destroy(tokens->next);
		if (tokens->value)
			free(tokens->value);
		free(tokens);
	}
}

static void	list_destroy(t_dict *list)
{
	t_dict	*next;

	while (list)
	{
		if (list->key)
			free(list->key);
		if (list->value)
			free(list->value);
		next = list->next;
		free(list);
		list = next;
	}
}

void	shell_destroy(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->line)
		free(shell->line);
	if (shell->cwd)
		free(shell->cwd);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->env_list)
		list_destroy(shell->env_list);
	if (shell->var_list)
		list_destroy(shell->var_list);
	if (shell->tokens)
		tokens_destroy(shell->tokens);
	if (shell->cmds)
		cmds_destroy(shell->cmds);
	free(shell);
}
