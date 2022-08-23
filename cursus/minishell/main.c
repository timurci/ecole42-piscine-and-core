#include <stdio.h>
#include "libft.h"
#include <readline/readline.h>

int	main(void)
{
	char	*rd;

	rd = NULL;
	while (!rd || ft_strcmp(rd, "exit"))
	{
		rd = readline(/*promt init func*/ NULL);
		if (/*command(rd)*/ 0)
			;//execute_command(rd);
		else
			;//routines(rd);
		free(rd);
	}
	return (0);
}
