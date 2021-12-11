#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*arr;
	unsigned int	i;
	unsigned int	size;

	if (min >= max)
		return (NULL);
	size = max - min;
	arr = (int *) malloc(sizeof(int) * (size));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = min++;
		if (++i == size)
			break ;
	}
	return (arr);
}

int	ft_ultimate_range(int **range, int min, int max)
{
	*range = ft_range(min, max);
	if (!*range)
		return (-1);
	return (max - min);
}
