/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:02:27 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/27 15:29:41 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# ifndef TYPE1TOKENS
#  define TYPE1TOKENS " 0.-#+"
# endif

# ifndef TYPE2TOKENS
#  define TYPE2TOKENS "cspdiuxX%"
# endif

/*
 * flags	0000 0000
 * #		0000 0001 (1)
 * +		0000 0010 (2)
 * -		0000 0100 (4)
 * 0		0000 1000 (8)
 * sp		0001 0000 (16)
 * .		0010 0000 (32)
 * swapped	0100 0000 (64)
 * capital	1000 0000 (128)
 */

typedef struct s_shape
{
	int		w0;
	int		w1;
	char	flags;
	int		slen;
}				t_shape;

int		ft_printf(const char *input, ...);

long	pformat(const char *input, int mem, int *print_len, va_list ap);

char	*conv_dec(long num, char type, t_shape *shape);
char	*conv_hex(unsigned long long num, char type, t_shape *shape);
char	*conv_str(char *s, t_shape *shape);

char	ft_tkncmp(char *s1, char *s2);

/*
 * alter_shape converts shape variables
 *
 * t1_checker checks and handles type1tokens and digit operations
 * returns 1 if (char c) violates the format syntax.
 */

void	alter_shape(t_shape *shape, int w0, int w1, char flags);
char	t1_checker(t_shape *shape, char c);

void	fill(char *s, char c, size_t len);
void	swap_ints(int *a, int *b);
char	*sharp_type(t_shape *shape);
char	*nullp_checker(char *s, t_shape *sh, char type);

#endif
