#include "push_swap.h"

t_ints	*dup_ints(t_ints *a)
{
	t_ints	*new_list;

	if (!a)
		return (NULL);
	new_list = malloc(sizeof(*new_list));
	if (!new_list)
		return (NULL);
	new_list->array = malloc(sizeof(int) * a->arr_size);
	if (!new_list)
	{
		free(new_list);
		return (NULL);
	}
	new_list->arr_size = a->arr_size;
	new_list->inventory = 0;
}

void	delete_ints(t_ints *list)
{
	if (!list)
		return ;
	if (list->array)
		free(list->array);
	free(list);
}
