#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdargs.h>
# include "libft.h"

# ifndef TYPE2TOKENS
#  define TYPE2TOKENS "cspdiuxX%"
# endif

int	ft_printf(const char *input, ...);

char	*ft_strfjoin(char *head, char *tail);
char	*ft_strffjoin(char *head, char *tail);

size_t	pformat(const char *input, size_t mem, char *store, va_list ap);

#endif
