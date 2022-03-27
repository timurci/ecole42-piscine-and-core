#include "ft_printf.h"

static char	*reshape(char *s, t_shape *sh)
{
	char	*news;

	swap_ints(&sh->w0, &sh->w1);
	if (!(sh->flags & 32) || (size_t) sh->w0 > ft_strlen(s))
		sh->w0 = ft_strlen(s);
	if (sh->w1 <= sh->w0)
		sh->w1 = sh->w0;
	else if ((size_t) sh->w1 < ft_strlen(s) && !(sh->flags & 32))
		sh->w1 = ft_strlen(s);
	news = malloc(sizeof(char) * (sh->w1 + 1));
	if (!news)
		return (NULL);
	news[sh->w1] = 0;
	if (*s == '%' && (sh->flags & 12) == 8 && ft_strlen(s) == 1)
		fill(news, '0', sh->w1);
	else
		fill(news, ' ', sh->w1);
	if (sh->flags & 4)
		ft_memcpy(news, s, sh->w0);
	else
		ft_memcpy(&news[sh->w1 - sh->w0], s, sh->w0);
	return (news);
}

char	*conv_str(char *s, t_shape *shape)
{
	if (!s)
		return (reshape("(null)", shape));
	return(reshape(s, shape));
}
