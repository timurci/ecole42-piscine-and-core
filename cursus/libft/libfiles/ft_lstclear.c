#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void(*del)(void *))
{
	t_list	*deleter;
	t_list	*leader;
	
	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	deleter = *lst;
	leader = deleter;
	while (leader)
	{
		leader = leader->next;
		ft_lstdelone(deleter, void(*del)(void *));
		deleter = leader;
	}
}
