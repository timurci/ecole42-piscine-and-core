#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s);

int	main(void)
{
	char	*s1 = "123456";

	printf("string:%s\n", s1);
	printf("strlen:\t%ld\n", strlen(s1));
	printf("ft_strlen:\t%ld\n", ft_strlen(s1));
	return (0);
}
