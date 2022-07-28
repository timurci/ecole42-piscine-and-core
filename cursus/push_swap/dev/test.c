#include "push_swap.h"

int	main(int ac, char **av)
{
	t_ints	*a;

	a = parse_args(ac, av);
	//print_array(a, "[UNS] a");
	while (!is_sorted(a))
	{
		if (a->inv <= 5)
			tiny_sort(a);
		else
			huge_sort(a);
	}
	//print_array(a, "[SRT] a");
	//free(a->arr);
	//free(a);
	return (0);
}
