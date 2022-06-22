/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:02:27 by tcakmako          #+#    #+#             */
/*   Updated: 2022/04/04 12:08:21 by tcakmako         ###   ########.fr       */
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

/*
 * w0 stores width field, w1 stores precision field. if there is no
 * width or precision field, then the variables are left in their
 * default values which is 0.
 *
 * the w0 and w1 differ semantically in recondition/reshape functions used
 * within conv_dec/conv_hex/conv_str function files. 
 * in that case w1 represents maximum length/width for the allocated string
 * and w0 represents the width of the target variable.
 * 		for example: "    123" has w1 of 7 and w0 of 3.
 * 
 * flags will be modified by t1_checker function according to the list 
 * provided in the flag table.
 * 		capital is a design flaw due to the limitations of norminette.
 * 		it is used in order to determine whether "x" is capital or not.
 * 
 * slen has a niche use and is a design flaw due to the limitations 
 * of norminette. only found in dec_conv, designed in order to handle 
 * null value in char type.
 */

/*
 * pformat is used to scan type2tokens and check if the format is valid.
 * if the format is valid, the variable is written to stdout and the 
 * written amount is added to integer print_len. if the format is invalid
 * then a negative value is returned.
 *
 * conv_dec/conv_hex/conv_str is used to take the appropriate variable
 * and return a string created allocated in heap according to the format.
 *
 * ft_tkncmp is an alternative strcmp function to compare type2tokens
 */

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
 *
 * fill function will fill from "s" address with "c" for "len" bytes.
 *
 * sharp_type is used in hexadecimal operations, used to determine
 * whether the initial letter "x" will be capitalized or not when
 * the token is "p" or "#" has been used. returns "0x" or "0X"
 *
 * nullp_checker has been designed to handle null values with "c"
 * or "xX" tokens. however, the "c" handling has been removed.
 * "type" passed "i" if it is from decimal operation or "h" if
 * it is from hexadecimal operation.
 */

void	alter_shape(t_shape *shape, int w0, int w1, char flags);
char	t1_checker(t_shape *shape, char c);

void	fill(char *s, char c, size_t len);
void	swap_ints(int *a, int *b);
char	*sharp_type(t_shape *shape);
char	*nullp_checker(char *s, t_shape *sh, char type);

#endif
