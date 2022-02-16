#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*temp;

	fd1 = open("file1", O_RDONLY);
	temp = get_next_line(1000);
	printf("%s\n", temp);
	free(temp);
	temp = get_next_line(fd1);
	printf("%s\n", temp);
	free(temp);
	fd2 = open("file2", O_RDONLY);
	temp = get_next_line(1001);
	printf("%s\n", temp);
	free(temp);
}
