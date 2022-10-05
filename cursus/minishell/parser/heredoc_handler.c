/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:47:45 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/05 21:17:44 by tcakmako         ###   ########.fr       */
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

static void	read_and_write_heredoc_input(t_shell *shell, char *file, int fd)
{
	char	*line;
	char	*prompt;

	prompt = ft_strjoin(file, " > ");
	line = readline(prompt);
	while (!shell->raised_error && line && ft_strcmp(file, line))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(prompt);
	}
	if (line)
		free(line);
	if (prompt)
		free(prompt);
	close(fd);
	exit(EXIT_SUCCESS);
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
	shell->doc_open = 1;
	shell->child_pid = fork();
	if (!shell->child_pid)
		read_and_write_heredoc_input(shell, file, fd);
	wait(NULL);
	close(fd);
	shell->doc_open = 0;
	shell->child_pid = -1;
	cmd->redir_input = new_file;
	cmd->input_type = REDIR_HEREDOC;
}
