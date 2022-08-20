#ifndef PHILO_H
# define PHILO_H

#include "ft_printf.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

/*
 * status 0 initial
 * status 1 dead
 * status 2 eating
 * status 3 sleeping
 * status 4 thinking
 */

typedef struct	s_table
{
	pthread_mutex_t	ffork_mtx;
	pthread_mutex_t	finish_mtx;
	int				free_forks;
	int				total_forks;
	int				*options;
	long			tv_start;
	char			dead_alert;
	int				n_finish;
} t_table;

typedef struct	s_philo
{
	pthread_t	th;
	char		forks;
	char		status;
	long		tv_last_act;
	int			index;
	int			has_eaten;
	t_table		*table;
} t_philo;

void			philosophers(int *options);

char			is_dead(t_philo *philo);
char			is_finished(t_philo *philo);
void			philo_eating_status(t_philo *philo);
void			*meal(void *param);

long			current_time(void);
unsigned int	passed(long n1, long n2);

int				ft_atoi(char *str);

#endif
