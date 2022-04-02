#include "push_swap.h"

void	print_list(char *tag, t_ints *ints)
{
	int	scan;

	scan = 0;
	printf("%s = [", tag);
	while (scan < ints->list_size)
	{
		printf("%d", ints->list[scan]);
		if (scan != ints->list_size - 1)
			printf(", ");
		scan++;
	}
	printf("]\n");
}

int	main(int ac, char **av)
{
	t_ints	*ints;
	t_ints	*sorted;

	if (ac > 2)
	{
		ints = convert_args(ac, av);
		if (!ints)
		{
			write(2, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		sorted = create_sorted(ints);
		print_list("ints  ", ints);
		print_list("sorted", sorted);
		//free(ints);
		//free(sorted);
	}
	exit(EXIT_SUCCESS);
}
