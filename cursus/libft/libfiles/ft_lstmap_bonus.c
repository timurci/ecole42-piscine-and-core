/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:50:50 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/08 14:58:40 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nl;
	t_list	*scanner;
	t_list	*subject;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	nl = lst;
	scanner = nl;
	while (lst)
	{
		subject = ft_lstnew(f(lst->content));
		if (!subject)
		{
			ft_lstclear(nl, del);
			return (NULL);
		}
		ft_lstadd_back(&scanner, subject);
		lst = lst->next;
		scanner = scanner->next;
	}
	return (nl);
}
