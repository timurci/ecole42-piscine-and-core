/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:48:34 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/14 15:07:12 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3000
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	check_nl(char **buffer, char **remainder);
void	clear_remains(char **remainder);
char	ft_strcmp(char *s1, char *s2);
void	*ft_calloc(size_t size);
char	*replace_str(char *old_str, char *new_str);
char	*ft_strfjoin(char *head, char *tail);
char	*check_cd(char *store, char *buffer, int fd);

#endif
