/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:53:57 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/07 17:30:52 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_and_join_threads(t_philo *philos)
{
	t_monitor	th_monitor;
	int			itr;

	itr = 0;
	th_monitor.table = philos->table;
	th_monitor.philos = philos;
	philos->table->tv_start = current_time();
	while (itr < philos->table->options[0])
	{
		pthread_create(&philos[itr].th, NULL, &meal, (void *) &philos[itr]);
		itr++;
	}
	pthread_create(&th_monitor.th, NULL, &monitor, (void *) &th_monitor);
	itr = 0;
	while (itr < philos->table->options[0])
	{
		pthread_join(philos[itr].th, NULL);
		itr++;
	}
	pthread_join(th_monitor.th, NULL);
}

static void	forks_mutex_destroy(t_fork *forks)
{
	t_fork	*initial;

	initial = forks;
	while (forks)
	{
		pthread_mutex_destroy(&forks->mutex);
		if (forks->prev == initial)
			break ;
		forks = forks->prev;
	}
}

static void	free_philos(t_philo *philos)
{
	if (philos->table)
	{
		forks_mutex_destroy(philos->table_forks);
		pthread_mutex_destroy(&philos->table->finish_mtx);
		pthread_mutex_destroy(&philos->table->print_mtx);
		free(philos->table->forks);
		free(philos->table);
	}
	free(philos);
}

void	philosophers(int *options)
{
	t_table	*table;
	t_philo	*philos;

	table = table_init(options);
	philos = philos_init(table);
	start_and_join_threads(philos);
	free_philos(philos);
}
