/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:19:36 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/10 12:19:37 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list static	*free_items(t_list *nl, t_list *element, void (*del)(void *))
{
	if (nl)
		ft_lstclear(&nl, del);
	ft_lstdelone(element, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nl;
	t_list	*nl_scanner;
	t_list	*element;

	nl = 0;
	while (lst)
	{
		element = ft_lstnew(f(lst->content));
		if (!element)
			return (free_items(nl, element, del));
		if (!nl)
			nl = element;
		else
			nl_scanner->next = element;
		nl_scanner = element;
		lst = lst->next;
	}
	return (nl);
}
