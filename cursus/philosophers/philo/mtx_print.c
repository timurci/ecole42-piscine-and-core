/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:53:46 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/23 11:53:47 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mtx_print(unsigned int time_passed, t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->print_mtx);
	ft_printf("%04ums %3d %s\n", time_passed, philo->index, msg);
	pthread_mutex_unlock(&philo->table->print_mtx);
}
