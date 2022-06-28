/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:44:21 by tcakmako          #+#    #+#             */
/*   Updated: 2022/06/28 12:44:21 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"

void	ft_putstr(char *str)
{
	unsigned int	size;

	size = 0;
	while (str[size])
		size++;
	write(1, str, size);
}

void	new_message(char *p_itr)
{
	if (*p_itr == -1)
	{
		ft_putstr("\nMSG: ");
		*p_itr = 0;
	}
}

void	sigusr_handler(int signal)
{
	static char				itr = -1;
	static unsigned char	store = 0;

	new_message(&itr);
	store = store << 1;
	if (signal == SIGUSR1)
		store |= 1;
	itr++;
	if (itr == 8)
	{
		write(1, &store, 1);
		itr = 0;
		if (store == 0)
			itr = -1;
		store = 0;
	}
}

int	main(void)
{
	struct sigaction	sigusr;

	sigusr.sa_handler = &sigusr_handler;
	sigusr.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sigusr, 0);
	sigaction(SIGUSR2, &sigusr, 0);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
