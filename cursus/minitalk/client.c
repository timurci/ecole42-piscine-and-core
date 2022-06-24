#include <signal.h>
#include <unistd.h>
#include <stdio.h> // printf
#include <stdlib.h> // atoi

void	send_char(pid_t pid, char c)
{
	char	itr;

	itr = 8;
	while (itr > 0)
	{
		if ((c >> --itr) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

void	send_message(pid_t pid, char *msg)
{
	char			itr;

	while (*msg)
		send_char(pid, *(msg++));
	send_char(pid, 0);
}

int	main(int ac, char **av)
{
	pid_t	server_pid;

	if (ac == 3)
	{
		server_pid = atoi(av[1]);
		send_message(server_pid, av[2]);
	}
	return (0);
}
