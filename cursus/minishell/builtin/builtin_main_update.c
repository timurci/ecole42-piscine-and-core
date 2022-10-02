#include "builtins.h"
#include "executor.h"

static int	is_ok(t_shell *shell, int i, int c_proccess)
{
	if (((!is_wait(shell->cmds[i]) && c_proccess < 2))
		|| (!is_wait(shell->cmds[i]) && i == 0 
		&& is_wait(shell->cmds[i + 1])))
			return (1);
	if (shell->cmds[i].wait_ctrl == 0 && operator_and(shell, i))
			return (1);
	if (shell->cmds[i].wait_ctrl == 1 && operator_or(shell, i))
			return (1);
	return (0);
}

void	builtin_main_update(t_shell *shell, int i, int c_proccess)
{
	if (shell->cmds[i].cmd && !ft_strcmp(shell->cmds[i].cmd, "cd")
		&& is_ok(shell, i, c_proccess))
		builtin_cd(shell, shell->cmds[i].argv);
	else if(shell->cmds[i].cmd 
		&& !ft_strcmp(shell->cmds[i].cmd, "export") && shell->cmds[i].argv[1]
		&& is_ok(shell, i, c_proccess))
		builtin_export(shell, shell->cmds[i].argv);
	else if(shell->cmds[i].cmd
		&& !ft_strcmp(shell->cmds[i].cmd, "unset")
		&& is_ok(shell, i, c_proccess))
		builtin_unset(shell, shell->cmds[i].argv);
	else if (shell->cmds[i].cmd && !ft_strcmp(shell->cmds[i].cmd, "exit"))
		builtin_exit(shell, shell);
	else if (is_assignment(&shell->cmds[i]) && is_ok(shell, i, c_proccess))
		builtin_assign(shell, shell->cmds[i].argv);
	builtin_sep_assign(shell, "?", ft_itoa(shell->cmds[i].exit_status));
}
