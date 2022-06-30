#include "push_swap.h"

int	main(int ac, char **av)
{
	t_ints	*a;

	if (ac == 2)
	{
		a = parse_args(av[1]);
		print_array(a, "[UNS] a");
		if (a->inv <= 3)
		{
			tiny_sort(a);
			print_array(a, "[SRT] a");
		}
	}
	else
		parsing_errors(0, NULL);
	return (0);
}
