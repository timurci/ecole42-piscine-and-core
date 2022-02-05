#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*linker;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		linker = ft_lstlast(*lst);
		linker->next = new;
	}
	if (!new)
		new->next = NULL;
}
