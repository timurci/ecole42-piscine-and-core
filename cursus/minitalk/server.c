#include <signal.h>
#include <unistd.h>
#include <stdio.h> // printf

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

	/*if (signal == SIGUSR1)
		write(1, "1\n", 2);
	else
		write(1, "0\n", 2);*/
	new_message(&itr);
	char sig = 0;
	if (signal == SIGUSR1)
		sig = 1;
	printf("sig: %d\titr: %d\tstr: %d\n", sig, itr, store);
	if (signal == SIGUSR1)
		store |= 1;
	store = store << 1;
	itr++;
	if (itr == 7)
	{
		printf("%c", store);
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
	//may need to add sa_restart flag
	printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
