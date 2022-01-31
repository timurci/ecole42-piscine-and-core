#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len);

int	main(void)
{
	int		i[] = {4, 2, 5, 6, 7, 8};
	int		*rtn_checker;
	size_t	scan = 0;

	
	printf("i:\t\t\t");
	while (scan < 6)
		printf("%d ", i[scan++]);
	rtn_checker = ft_memset(i, 1, 3);
	printf("\nft_memset (b, 1, 3):\t");
	scan = 0;
	while (scan < 6)
		printf("%d ", i[scan++]);
	if (rtn_checker == i)
		printf("\n[OK] The function returns i\n");
	else
		printf("\n[ER] The function does not return i\n");
	return (0);
}
