/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:48:34 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/16 14:43:31 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3000
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_remains
{
	char				*content;
	int					fd;
	struct s_remains	*next;
}				t_remains;

t_remains	*add_list(t_remains *lst, char *s, int fd);
t_remains	*check_fd(t_remains **lst, char **store, int fd);
char		*get_next_line(int fd);
char		check_nl(char **buffer, t_remains *remains);
void		clear_remains(t_remains **remains, int fd);
char		ft_strcmp(char *s1, char *s2);
void		*ft_calloc(size_t size);
char		*replace_str(char *old_str, char *new_str);
char		*ft_strfjoin(char *head, char *tail);
char		*check_cd(char *store, char *buffer, int fd, t_remains **remains);

#endif
