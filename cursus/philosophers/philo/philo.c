/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:53:57 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/23 11:53:59 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_table	*table_init(int *opts)
{
	t_table	*table;

	table = (t_table *) malloc(sizeof(*table));
	if (!table)
		return (NULL);
	table->total_forks = opts[0];
	table->free_forks = opts[0];
	table->options = opts;
	table->dead_alert = 0;
	table->n_finish = 0;
	pthread_mutex_init(&table->ffork_mtx, NULL);
	pthread_mutex_init(&table->finish_mtx, NULL);
	pthread_mutex_init(&table->print_mtx, NULL);
	return (table);
}

static t_philo	*philos_init(t_table *table)
{
	t_philo	*philos;
	int		itr;

	philos = (t_philo *) malloc(sizeof(*philos) * table->free_forks);
	if (!philos)
		return (NULL);
	itr = 0;
	while (itr < table->total_forks)
	{
		philos[itr].forks = 0;
		philos[itr].status = 0;
		philos[itr].has_eaten = 0;
		philos[itr].tv_last_act = -1;
		philos[itr].index = itr + 1;
		philos[itr].table = table;
		itr++;
	}
	return (philos);
}

static void	start_and_join_threads(t_philo *philos)
{
	int	itr;

	itr = 0;
	philos->table->tv_start = current_time();
	while (itr < philos->table->options[0])
	{
		pthread_create(&philos[itr].th, NULL, &meal, (void *) &philos[itr]);
		itr++;
	}
	itr = 0;
	while (itr < philos->table->options[0])
	{
		pthread_join(philos[itr].th, NULL);
		itr++;
	}
}

static void	free_philos(t_philo *philos)
{
	free(philos->table->options);
	if (philos->table)
	{
		pthread_mutex_destroy(&philos->table->ffork_mtx);
		pthread_mutex_destroy(&philos->table->finish_mtx);
		pthread_mutex_destroy(&philos->table->print_mtx);
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
