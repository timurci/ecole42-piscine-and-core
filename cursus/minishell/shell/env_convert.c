/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:20:52 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:24:24 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_dict	*env_to_list(char	**env)
{
	t_dict	*lst;
	char	*key;
	char	*value;
	char	*scan;

	if (!env)
		return (NULL);
	lst = NULL;
	while (*env)
	{
		key = *env;
		scan = *env;
		while (*scan != '=')
			scan++;
		key = ft_substr(key, 0, scan - key);
		value = ++scan;
		while (*scan)
			scan++;
		value = ft_substr(value, 0, scan - value);
		lst_add_back(&lst, key, value);
		env++;
	}
	return (lst);
}

static int	count_items(t_dict *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	**list_to_env(t_dict *lst)
{
	char	**env;
	char	*news;
	int		itr;

	if (!lst)
		return (NULL);
	env = malloc(sizeof(*env) * (count_items(lst) + 1));
	itr = 0;
	while (lst)
	{
		news = calloc(1, sizeof(char)
				* (ft_strlen(lst->key) + ft_strlen(lst->value) + 2));
		ft_strlcat(news, lst->key,
			ft_strlen(news) + ft_strlen(lst->key) + 1);
		ft_strlcat(news, "=",
			ft_strlen(news) + 2);
		ft_strlcat(news, lst->value,
			ft_strlen(news) + ft_strlen(lst->value) + 1);
		env[itr++] = news;
		lst = lst->next;
	}
	env[itr] = NULL;
	return (env);
}
