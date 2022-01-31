#include <unistd.h>

unsigned int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		write(1, argv[0], ft_strlen(argv[0]));
	return (0);
}
