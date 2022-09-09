/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:59:06 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/09 14:49:35 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	mtx_print(philo, "is sleeping");
	philo->status = 3;
	if (philo->table->options[3] < philo->table->options[1])
		usleep(philo->table->options[3] * 1000);
	else
		usleep((philo->table->options[1]
				- passed(current_time(), philo->tv_last_act)) * 1000);
}

static void	drop_forks(t_philo *philo)
{
	philo->status = 4;
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->table_forks->mutex);
	philo->fork_count--;
	philo->table_forks->exists++;
	mtx_print(philo, "has dropped a fork");
	pthread_mutex_unlock(&philo->table_forks->mutex);
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->table_forks->prev->mutex);
	philo->fork_count--;
	philo->table_forks->prev->exists++;
	mtx_print(philo, "has dropped a fork");
	pthread_mutex_unlock(&philo->table_forks->prev->mutex);
	philo_sleep(philo);
}

static void	try_to_get_fork(t_philo *philo, t_fork *fork)
{
	if (!fork)
		return ;
	pthread_mutex_lock(&fork->mutex);
	if (fork->exists)
	{
		fork->exists = 0;
		philo->fork_count++;
		mtx_print(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&fork->mutex);
}

static void	eat(t_philo *philo)
{
	while (philo->fork_count < 2)
	{
		if (is_dead(philo))
			return ;
		try_to_get_fork(philo, philo->table_forks);
		try_to_get_fork(philo, philo->table_forks->prev);
	}
	mtx_print(philo, "is eating");
	philo->status = 2;
	philo->has_eaten++;
	usleep(philo->table->options[2] * 1000);
	philo->tv_last_act = current_time();
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
	while (!is_dead(philo) && !is_finished(philo, 0))
	{
		time = current_time();
		if (time - philo->tv_last_act > 50 * 1000
			|| (time - philo->tv_last_act) > philo->table->options[1] / 10)
			eat(philo);
		else if (philo->status == 3
			&& (time - philo->table->tv_start) > philo->table->options[3])
		{
			mtx_print(philo, "is thinking");
			philo->status = 4;
		}
	}	
	return (NULL);
}
