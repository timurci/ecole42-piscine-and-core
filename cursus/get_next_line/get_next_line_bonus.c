/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:48:23 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/15 13:41:01 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_remains	*add_list(t_remains *lst, char *s, int fd)
{
	t_remains	*new_lst;

	new_lst = malloc(sizeof(t_remains));
	if (!new_lst)
		return (NULL);
	if (s)
		new_lst->content = replace_str(NULL, s);
	else
		new_lst->content = 0;
	new_lst->fd = fd;
	new_lst->next = 0;
	if (lst)
		lst->next = new_lst;
	return (new_lst);
}

t_remains	*check_fd(t_remains **lst, char **store, int fd)
{
	t_remains	*scanner;

	if (!*lst)
	{
		*lst = add_list(*lst, 0, fd);
		*store = ft_calloc(1);
	}
	scanner = *lst;
	if (scanner->fd != fd)
	{
		while (scanner && scanner->next && scanner->next->fd != fd)
			scanner = scanner->next;
	}	
	if (!scanner->next)
	{
		scanner->next = add_list(scanner, 0, fd);
		*store = ft_calloc(1);
	}
	else if (scanner->next->content == 0)
		*store = ft_calloc(1);
	else
		*store = replace_str(*store, scanner->next->content);
	return (scanner->next);
}

void	clear_remains(t_remains **remains, t_remains *curr_lst)
{
	t_remains	*scanner;

	scanner = *remains;
	if (scanner == curr_lst)
	{
		if (curr_lst->content)
			free(curr_lst->content);
		if (curr_lst->next)
			*remains = curr_lst->next;
		else
			*remains = 0;
		free(curr_lst);
	}
	else
	{
		while (scanner && scanner->next != curr_lst)
			scanner = scanner->next;
		scanner->next = curr_lst->next;
		if (curr_lst->content)
			free(curr_lst->content);
		free(curr_lst);
	}
}

char	check_nl(char **store, t_remains *remns)
{
	size_t	offset;
	size_t	pos_nl;
	char	has_nl;

	offset = 0;
	pos_nl = 0;
	has_nl = 0;
	while ((*store)[offset])
	{
		if ((*store)[offset] == '\n' && !has_nl)
		{
			pos_nl = offset;
			has_nl = 1;
		}
		offset++;
	}
	if (has_nl)
	{
		remns->content = replace_str(remns->content, &(*store)[pos_nl + 1]);
		(*store)[pos_nl + 1] = 0;
		*store = replace_str(*store, *store);
	}
	return (has_nl);
}

char	*get_next_line(int fd)
{
	t_remains static	*remains = 0;
	char				*store;
	char				*buffer;
	t_remains			*curr_lst;

	store = 0;
	buffer = 0;
	curr_lst = check_fd(&remains, &store, fd);
	buffer = ft_calloc(BUFFER_SIZE + 1);
	if (!buffer || !curr_lst || !store || fd < 0 || fd > 1000
		|| check_nl(&store, curr_lst))
		return (check_cd(store, buffer, fd));
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		store = ft_strfjoin(store, buffer);
		if (check_nl(&store, curr_lst))
			return (check_cd(store, buffer, fd));
	}
	clear_remains(&remains, curr_lst);
	return (check_cd(store, buffer, fd));
}
