#include <stdlib.h>
#include <stdargs.h>
#include "ft_printf.h"

char static	check_set(char c, char *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

size_t static	loc_set(char *s, char *set, size_t mem, int *width)
{
	char *scan;

	while (s[mem])
	{	
		scan = set;
		if (ft_isdigit(s[mem]))
		{
			*width = *width * 10 + (s[mem] - 48);
			if (s[mem + 1] && !(ft_digit(s[mem + 1]) || check_set(s[mem], set)))
				return (-1);
		}
		else if (check_set(s[mem], set))
			return (mem);
		mem++;
	}
	return (-1);
}

//format should also check for digits
char	*get_type(char *tn, va_list ap, int width)
{
	char			c;
	char			*s;
	void			*p;
	int				d;
	unsigned int	u;

	if (!ft_strcmp(tn, "c"))
		c = va_arg(ap, char);
	else if (!ft_strcmp(tn, "s"))
		s = va_arg(ap, char *);
	else if (!ft_strcmp(tn, "p"))
		p = va_arg(ap, void *);
	else if (!ft_strcmp(tn, "d") || !ft_strcmp(tn, "i"))
		d = va_arg(ap, int);
	else if (!ft_strcmp(tn, "u") || !ft_strcmp(tn, "x") || ft_strcmp(tn, "X"))
		u = va_arg(ap, unsigned int);
	//
	//
	//
	//
	//
	//
	//
	//
	//
}

size_t	pformat(const char *input, size_t mem, char *store, va_list ap)
{
	size_t	end;
	int		width;

	end = loc_set(input, TYPE2TOKEN, mem, &width);
	if (end < 0)
		return (-1);
	return (end + 1);
}
