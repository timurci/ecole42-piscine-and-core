/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:57 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 11:50:58 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*token_new(char *value, char type)
{
	t_token	*new_token_p;

	new_token_p = (t_token *) malloc(sizeof(t_token));
	if (!new_token_p)
		return (NULL);
	new_token_p->value = value;
	new_token_p->type = type;
	new_token_p->next = NULL;
	return (new_token_p);
}

void	token_append(t_token **token_pp, char *value, char type)
{
	t_token	*scan_p;

	if (!*token_pp)
		*token_pp = token_new(value, type);
	else
	{
		scan_p = *token_pp;
		while (scan_p->next)
			scan_p = scan_p->next;
		scan_p->next = token_new(value, type);
	}
}

t_token	*token_insert(t_token **token_pp, t_token *dst, char *value, char type)
{
	t_token	*new;
	t_token	*scan_p;

	new = NULL;
	if (!*token_pp)
	{
		new = token_new(value, type);
		*token_pp = new;
	}
	else
	{
		scan_p = *token_pp;
		while (scan_p && scan_p != dst)
			scan_p = scan_p->next;
		if (!scan_p)
			return (NULL);
		new = token_new(value, type);
		new->next = scan_p->next;
		scan_p->next = new->next;
	}
	return (new);
}

void	token_destroy(t_token **token_pp, t_token *target)
{
	t_token	*scan_p;

	if (!token_pp || !*token_pp || !target)
		return ;
	scan_p = *token_pp;
	if (scan_p == target)
	{
		*token_pp = scan_p->next;
		if (target->value)
			free(target->value);
		free(target);
	}
	else
	{
		while (scan_p && scan_p->next != target)
			scan_p = scan_p->next;
		if (!scan_p)
			return ;
		scan_p->next = target->next;
		if (target->value)
			free(target->value);
		free(target);
	}
}

t_token	*token_find_offset(t_token *tokens, t_token *target, int offset)
{
	int		target_offset;
	t_token	*scan_p;

	target_offset = 0;
	scan_p = tokens;
	while (scan_p && scan_p != target)
	{
		scan_p = scan_p->next;
		target_offset++;
	}
	target_offset += offset;
	if (target_offset < 0 || !scan_p)
		return (NULL);
	scan_p = tokens;
	while (target_offset)
	{
		scan_p = scan_p->next;
		target_offset--;
	}
	return (scan_p);
}
