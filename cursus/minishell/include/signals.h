#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include <readline/readline.h>

void	signal_handler(int signal);
void	sig_ctrlc(int sig);

#endif