#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);

}
