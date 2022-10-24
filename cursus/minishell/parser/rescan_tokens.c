/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescan_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:55:32 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/09 15:02:40 by ademirci         ###   ########.fr       */
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

static char	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static void	reset_flags(t_scanflag *flags)
{
	if (flags->has_pipe)
	{
		flags->has_prev_pipe = 1;
		flags->has_pipe = 0;
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

static void	reset_cmd(t_token *token, t_scanflag *flags)
{
	flags->has_cmd = 0;
	if ((flags->has_pipe || flags->has_prev_pipe) && is_builtin(token->value))
	{
		token->type = TTYPE_IGNORE;
		flags->force_ignore = 1;
	}
	else
	{
		flags->has_prev_cmd = 1;
		flags->force_ignore = 0;
	}
}

static t_token	*reset_types(t_token *tokens, t_token *scan, t_scanflag *flags)
{
	t_token	*prev;

	prev = NULL;
	while (tokens && tokens != scan)
	{
		if (tokens->type == TTYPE_ASSIGN || tokens->type == TTYPE_ARG)
		{
			if (!(prev && prev->type == TTYPE_REDIR)
				&& (flags->has_cmd || flags->force_ignore || (!flags->has_cmd
						&& !flags->has_prev_cmd && !ft_strlen(tokens->value))))
				tokens->type = TTYPE_IGNORE;
			else if (flags->has_prev_cmd)
				tokens->type = TTYPE_ARG;
			else if (!flags->has_cmd && !flags->has_prev_cmd
				&& prev && prev->type == TTYPE_IGNORE)
				tokens->type = TTYPE_CMD;
		}
		if (tokens->type == TTYPE_CMD)
			reset_cmd(tokens, flags);
		prev = tokens;
		tokens = tokens->next;
	}
	reset_flags(flags);
	return (tokens);
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
		while (scan && !(flags.has_pipe || flags.has_ctrl))
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
