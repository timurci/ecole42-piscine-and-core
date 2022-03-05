/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:02:27 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/05 12:02:54 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# ifndef TYPE2TOKENS
#  define TYPE2TOKENS "cspdiuxX%"
# endif

int		ft_printf(const char *input, ...);

char	*ft_strfjoin(char *head, char *tail);
char	*ft_strffjoin(char *head, char *tail);

size_t	pformat(const char *input, size_t mem, char **store, va_list ap);

char	*conv_dec(long num, char type, int width);
char	*conv_hex(unsigned int num, char type, int width);
char	*conv_str(char *str, int width);

char	ft_strcmp(char *s1, char *s2);

#endif
