#include "push_swap.h"

void	print_array(t_ints *list, char *name)
{
	size_t	itr;

	itr = 0;
	if (name)
		printf("%s = [", name);
	else
		printf("List = [");
	while (itr < list->inv)
	{
		printf("%d", list->arr[itr]);
		if (itr != list->inv - 1)
			printf(", ");
		itr++;
	}
	printf("]\n");
}
