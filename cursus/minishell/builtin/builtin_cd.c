#include "builtins.h"

int	builtin_cd(t_shell *shell, char **argv)
{
	argv++;
	if (chdir(*argv))
	{
		errors(shell, ERR_DIR, (void *) *argv);
		return (1);
	}
	if (shell->cwd)
		free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	if (shell->prompt)
		free(shell->prompt);
	shell->prompt = get_prompt(shell);
	return (0);
}
