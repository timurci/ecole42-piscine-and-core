#include "builtins.h"

int	pwd(t_shell *shell)
{
	printf("%s\n", shell->cwd);
	return (0);
}
