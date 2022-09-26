#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

int		builtin_cd(t_shell *shell, char **argv);
int		builtin_pwd(t_shell *shell);
int		builtin_echo(t_shell *shell, char **argv);

//builtin_assign.c
int		builtin_assign(t_shell *shell, char **argv);
int		builtin_single_assign(t_shell *shell, char *expr);
int		builtin_num_assign(t_shell *shell, char *key, int value);
char	*assignment_key_dup(char *expr);
char	*assignment_val_dup(char *expr);

#endif
