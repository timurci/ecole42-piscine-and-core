/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:55:31 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/09 14:49:06 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	is_dead(t_philo *philo)
{
	if (philo->table->dead_alert)
		return (1);
	return (0);
}

char	is_finished(t_philo *philo, char is_monitor)
{
	if (philo->table->options[4] == -1)
		return (0);
	if (!is_monitor && philo->has_eaten == philo->table->options[4])
	{
		pthread_mutex_lock(&philo->table->finish_mtx);
		philo->table->finish_count++;
		pthread_mutex_unlock(&philo->table->finish_mtx);
	}
	pthread_mutex_lock(&philo->table->finish_mtx);
	if (philo->table->finish_count == philo->table->options[0])
	{
		pthread_mutex_unlock(&philo->table->finish_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->finish_mtx);
	return (0);
}
