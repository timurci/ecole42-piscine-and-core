#include <stdlib.h>

long	get_size(int min, int max)
{
	long x;

	x = max - min;
	if (x < 0)
		return (-x);
	return (x);
}

void	fill_array(int *arr, int min, long size)
{
	long	i;
	
	i = 0;
	while (i < size)
	{
		arr[i] = min++;
		if (++i == size)
			break ;
	}
}

int	*ft_range(int min, int max)
{
	long 	size;
	int		*arr;

	if (min >= max)
		return (NULL);
	size = get_size(min, max);
	arr = (int *) malloc(sizeof(int) * size);
	if(!arr)
		return (NULL);
	fill_array(arr, min, size);
	return (arr);
}
