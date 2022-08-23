/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:12:45 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/08 14:15:37 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
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
		ft_lstdelone(deleter, del);
		deleter = leader;
	}
	*lst = NULL;
}
