#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"
# include "errors.h"

int		builtin_cd(t_shell *shell, char **argv);
int		builtin_pwd(t_shell *shell);
int		builtin_echo(char **argv);
int		builtin_export(t_shell *shell, char **argv);
int		builtin_env(t_shell *shell);
int		builtin_unset(t_shell *shell, char **argv);
int	    builtin_exit(t_shell *shell, void *param);

//builtin_assign.c
int		builtin_assign(t_shell *shell, char **argv);
int		builtin_single_assign(t_shell *shell, char *expr);
int		builtin_sep_assign(t_shell *shell, char *key, char *value);
char	*assignment_key_dup(char *expr);
char	*assignment_val_dup(char *expr);

//builtin_main_update.c
void	builtin_main_update(t_shell *shell, int i, int c_proccess);

#endif
