#include "ft_printf.h"

char	*conv_str(char *s)
{
	if (!s)
		return (ft_strdup("(null)"));
	return(ft_strdup(s));
}
