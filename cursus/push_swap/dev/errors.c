#include "push_swap.h"

void	parsing_errors(char mode, void *param)
{
	write(2, "Error\n", 6);
	if (mode == 0)
		printf("Incorrect number of arguments.\n");
	if (mode == 1)
		printf("Invalid argument at %u.\n", *((unsigned int *) param) + 1);
	exit(EXIT_FAILURE);
}
