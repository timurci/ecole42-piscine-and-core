#include "ft_printf.h"

char	*nullp_checker(char *s, t_shape *sh, char type)
{
	int		scan;
	char	*news;

	scan = 0;
	if (*s == 0 && sh->w1 == 1 && type != 'i')
	{
		sh->w1 = 0;
		return (s);
	}
	if (sh->w1 == 1)
		return (s);
	while (scan < sh->w1)
	{
		if (s[scan] == 0)
		{
			write(1, s, ft_strlen(s));
			write(1, &s[scan], 1);
			news = malloc(sizeof(char) * (sh->w1 - scan));
			news[sh->w1 - scan] = 0;
			ft_memcpy(news, &s[scan + 1], sh->w1 - scan - 1);
			sh->w1 = ft_strlen(news);
			free (s);
			return (news);
		}
		scan++;
	}
	return (s);
}
