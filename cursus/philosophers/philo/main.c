#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "philo.h"

static int	*options_init(int argc, char **argv)
{
	int	*opts;

	opts = (int *) malloc(sizeof(int) * 5);
	if (!ops)
		return (NULL);
	opts[0] = ft_atoi(argv[1]);
	opts[1] = ft_atoi(argv[2]);
	opts[2] = ft_atoi(argv[3]);
	opts[3] = ft_atoi(argv[4]);
	if (argc == 6)
		opts[4] = ft_atoi(argv[5]);
	else
		opts[4] = -1;
	return (opts);
}

int	main(int argc, char **argv)
{
	int	*options;
	if (!(argc == 5 || argc == 6))
		return (0);
	options = options_init(argc, argv);

}
