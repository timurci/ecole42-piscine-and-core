#ifndef PHILO_H
# define PHILO_H

#include "ft_printf.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct	s_table
{
	pthread_mutex_t	ffork_mtx;
	int				free_forks;
	int				total_forks;
	int				*options;
} t_table;

typedef struct	s_philo
{
	pthread_t	th;
	char		forks;
	char		status;
	long		tv_last_act;
	int			index;
	t_table		*table;
} t_philo;

void	philosophers(int *options);

long	current_time(void);

int		ft_atoi(char *str);

#endif
