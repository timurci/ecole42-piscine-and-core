#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "lexer.h"

int	main(int ac, char **av)
{
	char	**strs;
	int		itr;

	if (ac != 2)
		return (1);
	strs = split_tokens(av[1]);
	itr = 0;
	while (strs[itr])
		printf("%s\n", strs[itr++]);
	free(strs);
	return (0);
}
