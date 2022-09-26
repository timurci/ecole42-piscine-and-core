#include "builtins.h"

int	builtin_echo(t_shell *shell, char **argv)
{
	char	trail;

	argv++;
	trail = 1;
	if (*argv && !ft_strcmp(*argv, "-n"))
	{
		trail = 0;
		argv++;
	}
	else if (*argv)
		argv++;
	if (*argv)
		write(1, *argv, ft_strlen(argv));
	if (trail)
		write(1, "\n", 1);
	return (0);
}
