#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int	main(void)
{
	char	*s1 = "Hello World!";
	char	*s2 = "or";
	char	*result;

	printf("s1:\t%s\n", s1);
	printf("s2:\t%s\n", s2);
	result = ft_strnstr(s1, s2, 12);
	printf("ft_strnstr(s1, s2, 12)\n");
	if (result == 0)
		printf("NULL\n");
	else
		printf("res:\t%s\n", result);
	return (0);
}
