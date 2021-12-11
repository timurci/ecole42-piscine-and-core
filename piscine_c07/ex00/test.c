#include <stdio.h>

char	*ft_strdup(char *s);

int	main(int ac, char **av)
{
	char	*p;

	if (ac == 2)
	{
		p = ft_strdup(av[1]);
		printf("%s\n", p);
	}
	return (0);
}
