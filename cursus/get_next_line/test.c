#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	int		x;
	int		fd;
	char	*temp;

	x = 1;
	while (x < ac)
	{
		fd = open(av[x], O_RDONLY);
		
		temp = get_next_line(fd);
		printf("%s---\n", temp);
		if (temp)
			free(temp);
		temp = get_next_line(fd);
		printf("%s---\n", temp);
		if (temp)
			free(temp);
		temp = get_next_line(fd);
		printf("%s---\n", temp);
		if (temp)
			free(temp);
		close(fd);
		x++;
	}
	return (0);
}
