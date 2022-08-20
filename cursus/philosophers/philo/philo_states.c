#include "philo.h"

char	is_dead(t_philo *philo)
{
	long	time;

	if (philo->table->dead_alert)
		return (0); // 1
	time = current_time();
	if (time - philo->tv_last_act > philo->table->options[1])
	{
		philo->table->dead_alert = 1;
		ft_printf("%04u %3d died\n",
				(unsigned int) (current_time() - philo->table->tv_start),
				philo->index);
		return (0); // 1
	}
	return (0);
}

char	is_finished(t_philo *philo)
{
	if (philo->table->options[4] == -1)
		return (0);
	if (philo->has_eaten == philo->table->options[4])
	{
		pthread_mutex_lock(&philo->table->finish_mtx);
		philo->table->n_finish++;
		pthread_mutex_unlock(&philo->table->finish_mtx);
	}
	pthread_mutex_lock(&philo->table->finish_mtx);
	if (philo->table->n_finish == philo->table->options[0])
	{
		pthread_mutex_unlock(&philo->table->finish_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->finish_mtx);
	return (0);
}

void	philo_eating_status(t_philo *philo)
{
	philo->status = 2;
	philo->has_eaten++;
}
