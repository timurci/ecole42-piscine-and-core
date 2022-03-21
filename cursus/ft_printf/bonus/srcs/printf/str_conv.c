#include "ft_printf.h"

static char	*reshape(char *s, t_shape *sh)
{
	char	*news;

	if ((size_t) sh->w0 < ft_strlen(s))
		sh->w0 = ft_strlen(s);
	news = malloc(sizeof(char) * (sh->w0 + 1));
	if (!news)
		return (NULL);
	news[sh->w0] = 0;
	fill(news, ' ', sh->w0);
	if (sh->flags & 4)
		ft_memcpy(news, s, ft_strlen(s));
	else
		ft_memcpy(&news[sh->w0 - ft_strlen(s)], s, ft_strlen(s));
	return (news);
}

char	*conv_str(char *s, t_shape *shape)
{
	if (!s)
		return (ft_strdup("(null)"));
	return(reshape(s, shape));
}
