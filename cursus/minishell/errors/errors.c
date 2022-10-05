/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:25:17 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/04 16:38:55 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

static void	custom_perror(char *head, char *message, char *variable)
{
	if (head)
	{
		write(2, head, ft_strlen(head));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	if (variable)
	{
		write(2, " \'", 2);
		write(2, variable, ft_strlen(variable));
		write(2, "\'", 1);
	}
	write(2, "\n", 1);
}

static void	syntax_errors(char mode, void *param)
{
	if (mode == ERR_QUOTE)
		custom_perror(ERR_SHELL, ERR_QUOTE_MSG, NULL);
	else if (mode == ERR_COLUMN)
		custom_perror(ERR_SHELL, ERR_COLUMN_MSG, NULL);
	else if (mode == ERR_TOKEN)
		custom_perror(ERR_SHELL, ERR_TOKEN_MSG, (char *) param);
	else if (mode == ERR_ASSIGN)
		custom_perror(ERR_SHELL, ERR_ASSIGN_MSG, (char *) param);
}

static void	file_errors(char mode, void *param)
{
	if (mode == ERR_REDIR)
		custom_perror("*", ERR_REDIR_MSG, NULL);
	else if (mode == ERR_DIR)
		perror((const char *) param);
	else if (mode == ERR_PATH)
		custom_perror(ERR_SHELL, ERR_PATH_MSG, (char *) param);
}

void	errors(t_shell *shell, char mode, void *param)
{
	if (mode < 5)
		syntax_errors(mode, param);
	else if (mode < 10)
		file_errors(mode, param);
	shell->raised_error = 1;
}
