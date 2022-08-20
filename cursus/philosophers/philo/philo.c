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
	if (pthread_mutex_init(&table->ffork_mtx, NULL))
	{
		free(table);
		return (NULL);
	}
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
		philos[itr]->forks = 0;
		philos[itr]->status = 0;
		philos[itr]->tv_last_act = -1;
		philos[itr]->index = itr;
		philos[itr]->table = table;
		itr++;
	}
}

void	philosophers(int *options)
{
	t_table	*table;
	t_philo	*philos;

	table = table_init(options);
	philos = philos_init(table);
}
