/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:53:46 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/07 16:39:34 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_msg(t_philo *philo, char *msg)
{
	printf("%04ums %3d %s\n", passed(current_time(), philo->table->tv_start),
		philo->index, msg);
}

void	mtx_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->print_mtx);
	if (current_time() - philo->tv_last_act > philo->table->options[1])
	{
		philo->table->dead_alert = 1;
		print_msg(philo, "died");
	}
	else
		print_msg(philo, msg);
	pthread_mutex_unlock(&philo->table->print_mtx);
}
