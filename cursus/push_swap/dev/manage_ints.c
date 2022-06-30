#include "push_swap.h"

t_ints	*dup_ints(t_ints *a)
{
	t_ints	*new_list;

	if (!a)
		return (NULL);
	new_list = malloc(sizeof(*new_list));
	if (!new_list)
		return (NULL);
	new_list->arr = malloc(sizeof(int) * a->max);
	if (!new_list)
	{
		free(new_list);
		return (NULL);
	}
	new_list->max = a->max;
	new_list->inv = 0;
	return (new_list);
}

void	delete_ints(t_ints *list)
{
	if (!list)
		return ;
	if (list->arr)
		free(list->arr);
	free(list);
}
