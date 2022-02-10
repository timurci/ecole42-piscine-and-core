#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int		read_index;
	int		fd;
	char	*result;

	read_index = 1;
	while (read_index < ac)
	{
		fd = open(av[read_index], O_RDONLY);
		result = get_next_line(fd);
		printf("%s", result);
		free(result);
		close(fd);
		read_index++;
	}
	return (0);
}
