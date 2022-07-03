#include "push_swap.h"

int	main(int ac, char **av)
{
	t_ints	*a;

	if (ac == 2)
	{
		a = parse_args(av[1]);
		print_array(a, "[UNS] a");
		while (!is_sorted(a))
		{
			if (a->inv <= 5)
				tiny_sort(a);
			else
			{
				printf("CANNOT SORT ARGS\n");
				break ;
			}	
		}
		print_array(a, "[SRT] a");
	}
	else
		parsing_errors(0, NULL);
	free(a->arr);
	free(a);
	return (0);
}
