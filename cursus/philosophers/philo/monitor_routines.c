/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:44:54 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/09 14:49:51 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->table->options[0])
	{
		if (current_time() - philos[i].tv_last_act > philos->table->options[1])
		{
			philos->table->dead_alert = 1;
			mtx_print(&philos[i], "died");
			return ;
		}
		i++;
	}
}

void	*monitor(void *param)
{
	t_monitor	*monitor;

	usleep(50);
	monitor = (t_monitor *) param;
	while (!monitor->table->dead_alert && !is_finished(monitor->philos, 1))
	{
		check_death(monitor->philos);
		usleep(1000);
	}
	return (NULL);
}
