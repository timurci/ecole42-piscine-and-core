/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:47:45 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/25 14:15:59 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*find_absent_filename(char *filename, int count)
{
	char	*count_str;
	char	*path;

	count_str = ft_itoa(count);
	filename = ft_strjoin(filename, count_str);
	free(count_str);
	path = ft_strjoin("/tmp/", filename);
	free(filename);
	if (!access(path, F_OK))
	{
		free(path);
		return (NULL);
	}
	return (path);
}

static int	open_file_at_tmp(char **filename_p)
{
	char	*file;
	int		fd;
	int		count;

	fd = -1;
	count = 0;
	file = find_absent_filename(*filename_p, count);
	while (file == NULL && count < 100)
		file = find_absent_filename(*filename_p, ++count);
	if (!file)
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT);
	if (fd < 0)
	{
		perror(file);
		free(file);
		return (fd);
	}
	*filename_p = file;
	return (fd);
}

static void	read_and_write_heredoc_input(char *file, int fd)
{
	char	*line;
	char	*prompt;
	char	written;

	prompt = ft_strjoin(file, " > ");
	line = readline(prompt);
	written = 0;
	while (line && ft_strcmp(file, line))
	{
		if (!written)
			written = 1;
		else
			write(fd, " ", 1);
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline(prompt);
	}
	if (line)
		free(line);
	if (prompt)
		free(prompt);
}

void	heredoc_handler(t_shell *shell, t_cmd *cmd, t_token *token)
{
	char	*new_file;
	char	*file;
	int		fd;

	file = token->value;
	new_file = token->value;
	fd = open_file_at_tmp(&new_file);
	if (fd < 0)
	{
		shell->raised_error = 1;
		return ;
	}
	read_and_write_heredoc_input(file, fd);
	close(fd);
	cmd->redir_input = new_file;
	cmd->input_type = REDIR_HEREDOC;
}
