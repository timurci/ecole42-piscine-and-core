#include "philo.h"

long	current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

unsigned int	passed(long n1, long n2)
{
	return (n1 - n2);
}
