#include "push_swap.h"

void	parsing_errors(char mode, void *param)
{
	write(2, "Error\n", 6);
	if (mode == 0)
		printf("Incorrect number of arguments.\n");
	else if (mode == 1)
		printf("Invalid argument at %u.\n", *((unsigned int *) param + 1));
	else if (mode == 2)
		printf("Repeated argument at %u.\n", *((unsigned int *) param));
	exit(EXIT_FAILURE);
}
