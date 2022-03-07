/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:02:27 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/05 17:45:06 by tcakmako         ###   ########.fr       */
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

long	pformat(const char *input, long mem, char **store, va_list ap);

char	*conv_dec(long num, char type);
char	*conv_hex(unsigned long long num, char type);

char	ft_tkncmp(char *s1, char *s2);

#endif
