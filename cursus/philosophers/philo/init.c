/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:36:54 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/07 16:36:55 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork	*fork_init(int *opts)
{
	t_fork	*forks;
	int		itr;

	forks = malloc(sizeof(*forks) * opts[0]);
	if (!forks)
		return (NULL);
	itr = 0;
	while (itr < opts[0])
	{
		if (itr > 0)
			forks[itr].prev = &forks[itr - 1];
		forks[itr].exists = 1;
		pthread_mutex_init(&forks[itr].mutex, NULL);
		itr++;
	}
	forks[0].prev = NULL;
	if (opts[0] > 1)
		forks[0].prev = &forks[opts[0] - 1];
	return (forks);
}

t_table	*table_init(int *opts)
{
	t_table	*table;

	table = (t_table *) malloc(sizeof(*table));
	if (!table)
		return (NULL);
	table->forks = fork_init(opts);
	table->options = opts;
	table->dead_alert = 0;
	table->finish_count = 0;
	pthread_mutex_init(&table->finish_mtx, NULL);
	pthread_mutex_init(&table->print_mtx, NULL);
	return (table);
}

t_philo	*philos_init(t_table *table)
{
	t_philo	*philos;
	int		itr;

	philos = (t_philo *) malloc(sizeof(*philos) * table->options[0]);
	if (!philos)
		return (NULL);
	itr = 0;
	while (itr < table->options[0])
	{
		philos[itr].table_forks = &table->forks[itr];
		philos[itr].fork_count = 0;
		philos[itr].status = 0;
		philos[itr].has_eaten = 0;
		philos[itr].tv_last_act = -1;
		philos[itr].index = itr + 1;
		philos[itr].table = table;
		itr++;
	}
	return (philos);
}
