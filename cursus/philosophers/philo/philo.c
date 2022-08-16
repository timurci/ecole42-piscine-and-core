#include "philo.h"

static t_table	*table_init(int *opts)
{
	t_table	*table;

	table = (t_table *) malloc(sizeof(*table));
	if (!table)
		return (NULL);
	if (opts[0] == 1)
		table->total_forks = 1;
	else
		table->total_forks = opts[0] - 1;
	table->free_forks = table->total_forks;
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

}

void	philosophers(int *options)
{
	t_table	*table;
	t_philo	*philos;

	table = table_init(options);
	philos = philos_init(table);
}
