#include <stdio.h>

void	*ft_bzero(void *s, size_t n);

int	main(void)
{
	int		i[] = {4, 2, 5, 6, 7, 8};
	size_t	scan = 0;

	
	printf("i:\t\t\t");
	while (scan < 6)
		printf("%d ", i[scan++]);
	ft_bzero(i, 3);
	printf("\nft_bzero (s, 3):\t");
	scan = 0;
	while (scan < 6)
		printf("%d ", i[scan++]);
	return (0);
}
