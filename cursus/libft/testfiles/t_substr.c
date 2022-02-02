#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

int	main(void)
{
	printf("%s\n", ft_substr("Hello World!", 7, 2));
	return (0);
}
