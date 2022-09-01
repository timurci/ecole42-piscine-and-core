#include "shell.h"

char	*get_prompt(t_shell *shell)
{
	char	*latter_dir;
	char	*prompt;

	if (!shell->cwd)
		shell->cwd = getcwd(NULL, 0);
	latter_dir = ft_strrchr(shell->cwd, '/');
	if (!latter_dir)
		return (ft_strdup("shell > "));
	if (ft_strlen(latter_dir) == 1)
		return (ft_strdup("shell / > "));
	else
	{
		latter_dir = ft_strdup(latter_dir + 1);
		prompt = ft_strjoin(ft_strdup("shell "), latter_dir);
		free(latter_dir);
		prompt = ft_strjoin(prompt, " > ");
		return (prompt);
	}
}

t_shell	*shell_init(t_dict *env_list)
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
	if (env_list)
		shell->env_list = /*env_init(env_list)*/ NULL;
	return (shell);
}
