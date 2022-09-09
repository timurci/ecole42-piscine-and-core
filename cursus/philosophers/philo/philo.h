/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:55:17 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/09 14:25:41 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

/*
 * status 0 initial
 * status 1 dead
 * status 2 eating
 * status 3 sleeping
 * status 4 thinking
 */

typedef struct s_fork
{
	char			exists;
	pthread_mutex_t	mutex;
	struct s_fork	*prev;
}	t_fork;

typedef struct s_table
{
	pthread_mutex_t	finish_mtx;
	pthread_mutex_t	print_mtx;
	t_fork			*forks;
	int				*options;
	long			tv_start;
	char			dead_alert;
	int				finish_count;
}	t_table;

typedef struct s_philo
{
	pthread_t	th;
	t_fork		*table_forks;
	char		fork_count;
	char		status;
	long		tv_last_act;
	int			index;
	int			has_eaten;
	t_table		*table;
}	t_philo;

typedef struct s_monitor
{
	pthread_t	th;
	t_table		*table;
	t_philo		*philos;
}	t_monitor;

t_table			*table_init(int *opts);
t_philo			*philos_init(t_table *table);

void			philosophers(int *options);

char			is_dead(t_philo *philo);
char			is_finished(t_philo *philo);
void			philo_eating_status(t_philo *philo);
void			*meal(void *param);
void			*monitor(void *param);

long			current_time(void);
unsigned int	passed(long n1, long n2);

void			mtx_print(t_philo *philo, char *msg);
int				ft_atoi(char *str);

#endif
