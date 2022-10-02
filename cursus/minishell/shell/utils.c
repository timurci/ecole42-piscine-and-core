/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:57:52 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 11:57:53 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lst_add_front(t_dict **list, char *key, char *value)
{
	t_dict	*new;

	new = malloc(sizeof(t_dict));
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (*list != NULL)
		new->next = *list;
	*list = new;
}

void	lst_add_back(t_dict **list, char *key, char *value)
{
	t_dict	*new;
	t_dict	*tmp;

	tmp = *list;
	new = malloc(sizeof(t_dict));
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		while (tmp->next != NULL && tmp != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_dict	*lst_find_entry(t_dict *list, char *key)
{
	while (list != NULL)
	{
		if (!ft_strcmp(list->key, key))
			return (list);
		list = list->next;
	}
	return (NULL);
}

char	*lst_find_value(t_dict *list, char *key)
{
	t_dict	*found;

	found = lst_find_entry(list, key);
	if (!found)
		return (NULL);
	return (found->value);
}

void	lst_destroy_entry(t_dict **list, char *key)
{
	t_dict	*back;
	t_dict	*tmp;
	int		i;

	tmp = *list;
	back = *list;
	i = 0;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, key))
			break ;
		if (i != 0)
			back = back->next;
		tmp = tmp->next;
        i++;
	}
	back->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}
