#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len);

int	main(void)
{
	char	*block;
	char	*src;
	char	*dst;
	char	*holder;

	block = malloc(sizeof(char) * 13);
	src = strcpy(block, "123456");
	holder = strdup(src);
	dst = src + 3;
	memmove(dst, src, 3);
	if (strncmp(dst, holder, 3))
		printf("[ER] dst does not match src\n");
	else
		printf("[OK] dst matches src\n");
	return (0);
}
