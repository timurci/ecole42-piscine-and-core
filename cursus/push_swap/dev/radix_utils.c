#include "push_swap.h"

char	is_skippable(t_ints *l, char itr)
{
	char	flag;
	size_t	scan;

	flag = 1;
	scan = 0;
	while (flag && scan < l->inv)
	{
		if (l->arr[scan] >> itr)
			flag = 0;
		scan++;
	}
	return (flag);
}	
