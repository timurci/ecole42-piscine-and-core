#include <stdio.h>

void	ft_sort_int_tab(int *tab, int size);

int	main(void)
{
	int array[7] = {5, 3, 6, 1, 4, 8, 9};
	int	size;
	int	index;

	size = 7;
	index = 0;
	ft_sort_int_tab(array, size);
	while (index < size)
	{
		printf("%d ", array[index]);
		index++;
	}
	printf("\n");

	return (0);
}
