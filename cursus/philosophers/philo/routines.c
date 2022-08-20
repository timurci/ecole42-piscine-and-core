#include "philo.h"

static void	philo_sleep(t_philo *philo)
{
	long	time;

	if (is_dead(philo))
		return ;
	time = current_time();
	ft_printf("%04ums %3d is sleeping\n",
			passed(time, philo->table->tv_start), philo->index);
	if (philo->status != 4)
		philo->tv_last_act = time;
	philo->status = 3;
	usleep(philo->table->options[3] * 1000);
}

static void	drop_forks(t_philo *philo)
{
	philo->tv_last_act = passed(current_time(), philo->table->tv_start);
	philo->status = 4;
	while (philo->forks > 0)
	{
		if (is_dead(philo))
			return ;
		pthread_mutex_lock(&philo->table->ffork_mtx);
		philo->forks -= 2;
		philo->table->free_forks += 2;
		ft_printf("%04ums %3d has dropped two forks\n",
				passed(current_time(), philo->table->tv_start), philo->index);
		pthread_mutex_unlock(&philo->table->ffork_mtx);
	}
	philo_sleep(philo);
}

static void	eat(t_philo *philo)
{
	long	time;

	while (philo->forks < 2)
	{
		if (is_dead(philo))
			return ;
		pthread_mutex_lock(&philo->table->ffork_mtx);
		if (philo->table->free_forks > 0)
		{
			philo->table->free_forks -= 2;
			philo->forks += 2;
			time = current_time();
			ft_printf("%04ums %3d has taken two forks\n",
					passed(time, philo->table->tv_start), philo->index);
		}
		pthread_mutex_unlock(&philo->table->ffork_mtx);
	}
	ft_printf("%04ums %3d is eating\n",
			passed(time, philo->table->tv_start), philo->index);
	philo->tv_last_act = time;
	philo_eating_status(philo);
	usleep(philo->table->options[2] * 1000);
	drop_forks(philo);
}

void	*meal(void	*param)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *) param;
	philo->tv_last_act = current_time();
	if (philo->index % 2 == 0)
		eat(philo);
	else
		philo_sleep(philo);
	while (!is_dead(philo) && !is_finished(philo))
	{
		time = current_time();
		if ((time - philo->table->tv_start) / 2 > philo->table->options[1])
			eat(philo);
		else if (philo->status == 3 &&
				time - philo->table->tv_start > philo->table->options[3])
		{
			ft_printf("%04ums %3d is thinking\n",
					passed(time, philo->table->tv_start), philo->index);
			philo->status = 4;
		}
	}	
	return (NULL);
}
