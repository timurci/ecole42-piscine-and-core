#ifndef PHILO_H
# define PHILO_H

typedef struct	s_table
{
	pthread_mutex_t	ffork_mtx;
	int				free_forks;
	int				total_forks;
} t_table;

typedef struct	s_philo
{
	pthread_t	th;
	char		forks;
	t_table		*table;
} t_philo;

int	ft_atoi(char *str);

#endif
