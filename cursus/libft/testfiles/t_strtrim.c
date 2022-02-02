#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set);

int	main(void)
{
	printf("%s\n", ft_strtrim("---aa--bbbcas-qwe----", "--"));
	return (0);
}
