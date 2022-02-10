/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:12:31 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/10 14:37:14 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3065
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*alloc_str(char *buffer, size_t memsize);
char	*realloc_str(char *base, char *tail);

#endif
