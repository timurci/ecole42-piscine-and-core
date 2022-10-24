/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:20:44 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/11 20:45:28 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_args(t_token *tokens)
{
	int		itr;
	t_token	*scan_p;
	t_token	*prev;

	itr = 0;
	scan_p = tokens;
	while (scan_p && scan_p->type != TTYPE_PIPE && scan_p->type != TTYPE_CTRL)
	{
		prev = token_find_offset(tokens, scan_p, -1);
		if (scan_p->type == TTYPE_ARG && prev && prev->type != TTYPE_REDIR)
			itr++;
		else if (scan_p->type == TTYPE_ASSIGN)
			itr++;
		else if (scan_p->type == TTYPE_CMD)
			itr++;
		scan_p = scan_p->next;
	}
	return (itr);
}

static t_token	*set_redir(t_shell *shell, t_cmd *cmd, t_token *tokens)
{
	char	*file;

	file = NULL;
	if (tokens->next)
		file = tokens->next->value;
	if (*(tokens->value) == '<')
		cmd->redir_input = file;
	else
		cmd->redir_output = file;
	if (!ft_strcmp(tokens->value, "<"))
		cmd->input_type = REDIR_INPUT;
	else if (!ft_strcmp(tokens->value, "<<"))
		heredoc_handler(shell, cmd, tokens->next);
	else if (!ft_strcmp(tokens->value, ">"))
		cmd->output_type = REDIR_OUTPUT;
	else
		cmd->output_type = REDIR_APPEND;
	return (tokens->next);
}

t_token	*fill_one_cmd(t_shell *shell, t_cmd *cmds, t_cmd *cmd, t_token *tokens)
{
	int	itr_args;

	while (is_cmd_end(tokens))
	{
		if (!ft_strcmp(tokens->value, "||"))
			cmd->wait_ctrl = 1;
		else if (!ft_strcmp(tokens->value, "&&"))
			cmd->wait_ctrl = 0;
		tokens = tokens->next;
	}
	tokens = check_brackets(cmds, cmd, tokens);
	cmd->argv = (char **) ft_calloc(count_args(tokens) + 1, sizeof(char *));
	itr_args = 0;
	while (tokens && !is_cmd_end(tokens))
	{
		if (tokens->type == TTYPE_CMD)
			cmd->cmd = tokens->value;
		if (tokens->type == TTYPE_CMD || tokens->type == TTYPE_ARG
			|| tokens->type == TTYPE_ASSIGN)
			cmd->argv[itr_args++] = tokens->value;
		else if (tokens->type == TTYPE_REDIR)
			tokens = set_redir(shell, cmd, tokens);
		tokens = tokens->next;
	}
	return (tokens);
}

static int	count_procs(t_token *tokens)
{
	int	itr;

	itr = 0;
	while (tokens)
	{
		if (tokens->type == TTYPE_PIPE || tokens->type == TTYPE_CTRL)
			itr++;
		tokens = tokens->next;
	}
	return (itr + 1);
}

t_cmd	*split_cmds(t_shell *shell, t_token *tokens)
{
	t_cmd	*cmds;
	int		itr;

	cmds = (t_cmd *) ft_calloc(count_procs(tokens) + 1, sizeof(*cmds));
	itr = 0;
	while (tokens)
	{
		cmds[itr].exit_status = -1;
		cmds[itr].wait_ctrl = -1;
		if (!(!tokens->next
				&& tokens->type != TTYPE_CMD && tokens->type != TTYPE_ASSIGN))
			tokens = fill_one_cmd(shell, cmds, &cmds[itr++], tokens);
		else
			tokens = tokens->next;
	}
	cmds[itr].exit_status = -1;
	cmds[itr].wait_ctrl = -1;
	cmds[itr].is_last = 1;
	return (cmds);
}
