/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescan_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:55:32 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/24 18:21:59 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescan_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:55:32 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/22 15:23:24 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*static char	has_initial_cmd(t_token *scan, t_token *prev)
{
	if (scan->type == TTYPE_CMD
		&& (prev == NULL || prev->type == TTYPE_CTRL))
		return (1);
	return (0);
}

static char	has_pipe_or_latter_cmd(t_token *scan, t_token *prev)
{
	if (scan->type == TTYPE_CMD || scan->type == TTYPE_PIPE
		|| (prev && prev->type == TTYPE_PIPE))
		return (1);
	return (0);
}

t_token	*reset_type_for_assignments(t_token *tks, t_token *scan, char has_cmd)
{
	while (tks && tks != scan)
	{
		if (tks->type == TTYPE_ASSIGN)
		{
			if (has_cmd == 1)
				tks->type = TTYPE_IGNORE;
			else if (has_cmd == -1)
				tks->type = TTYPE_ARG;
		}
		else if (tks->tpye == TTYPE_CMD && has_cmd == -1
		tks = tks->next;
	}
	return (tks);
}

void	rescan_tokens(t_token *tokens)
{
	char	has_cmd;
	char	has_ctrl;
	t_token	*scan;
	t_token	*prev;

	scan = tokens;
	prev = NULL;
	while (tokens)
	{
		has_cmd = 0;
		stop = 0;
		while (scan && !stop)
		{
			if (has_initial_cmd(scan, prev))
				has_cmd = -1;
			else if (!has_cmd && has_pipe_or_latter_cmd(scan, prev))
				has_cmd = 1;
			if (scan->type == TTYPE_CTRL || scan->type == TTYPE_PIPE)
				stop = 1;
			prev = scan;
			scan = scan->next;
		}
		tokens = reset_type_for_assignments(tokens, scan, has_cmd);
	}
}*/

static void	reset_flags(t_scanflag *flags)
{
	if (flags->has_pipe)
	{
		flags->has_pipe = 0;
		flags->has_prev_pipe = 1;
		flags->has_cmd = 0;
		flags->has_prev_cmd = 0;
	}
	if (flags->has_ctrl)
	{
		flags->has_cmd = 0;
		flags->has_prev_cmd = 0;
		flags->has_prev_pipe = 0;
		flags->has_ctrl = 0;
		flags->force_ignore = 0;
	}
}

static t_token	*reset_types(t_token *tokens, t_token *scan, t_scanflag *flags)
{
	if (flags->has_prev_pipe || flags->has_pipe)
		flags->force_ignore = 1;
	while (tokens && tokens != scan)
	{
		if (tokens->type == TTYPE_ASSIGN)
		{
			if (flags->has_cmd || flags->force_ignore)
				tokens->type = TTYPE_IGNORE;
			else if (flags->has_prev_cmd)
				tokens->type = TTYPE_ARG;
		}
		else if (tokens->type == TTYPE_CMD)
		{
			flags->has_cmd = 0;
			if (flags->force_ignore && !ft_strcmp(tokens->value, "export"))
				tokens->type = TTYPE_IGNORE;
			else
				flags->has_prev_cmd = 1;
		}
		tokens = tokens->next;
	}
	reset_flags(flags);
	return (tokens);
}

static char	stop_condition(t_scanflag *flags)
{
	return (flags->has_pipe || flags->has_ctrl);
}

void	rescan_tokens(t_token *tokens)
{
	t_scanflag	flags;
	t_token		*scan;

	flags.has_cmd = 0;
	flags.has_prev_cmd = 0;
	flags.has_pipe = 0;
	flags.has_prev_pipe = 0;
	flags.has_ctrl = 0;
	flags.force_ignore = 0;
	scan = tokens;
	while (tokens)
	{
		while (scan && !stop_condition(&flags))
		{
			if (scan->type == TTYPE_CMD)
				flags.has_cmd = 1;
			else if (scan->type == TTYPE_PIPE)
				flags.has_pipe = 1;
			else if (scan->type == TTYPE_CTRL)
				flags.has_ctrl = 1;
			scan = scan->next;
		}
		tokens = reset_types(tokens, scan, &flags);
	}
}
