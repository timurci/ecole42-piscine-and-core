#include <stdio.h> // replace with ft_printf.h
#include <string.h> // replace strlen atoi isdigit
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_ints
{
	int		*list;
	int		list_size;
}				t_ints;

t_ints	*convert_args(int ac, char **av);
t_ints	*create_sorted(t_ints *ints);
int		fatoi(char *str);
