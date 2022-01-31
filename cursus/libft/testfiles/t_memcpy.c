#include <stdio.h>

void	*ft_memcpy(void *restrict dt, const void *restrict sc, size_t n);

int	main(void)
{
	char	*src = "Hello World!";
	char	dst[] = "Plane pilot";
	char	*ctrl;

	printf("src:\t%s\n", src);
	printf("dst:\t%s\n", dst);
	ctrl = ft_memcpy(dst, src, 5);
	printf("ft_memcpy(dst, src, 5)\n");
	printf("dst:\t%s\n", dst);
	if (ctrl == dst)
		printf("[OK] The function returns dst\n");
	else
		printf("[ER] The function does not return dst\n");
	return (0);
}
