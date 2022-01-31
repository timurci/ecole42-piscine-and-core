#include <stdlib.h>

unsigned int	str_size(char *s)
{
	unsigned int	sz;

	sz = 0;
	while (s[sz] != 0)
		sz++;
	return (sz);
}

unsigned int	final_size(int size, char **strs, unsigned int sep_size)
{
	unsigned int	s;
	int		i;

	s = 0;
	i = 0;
	while (i < size)
		s += str_size(strs[i++]) + sep_size;
	s -= sep_size;
	return (s + 1);
}

char	*place_str(char *p, char *str)
{
	while (*str != 0)
		*(p++) = *(str++);
	return (p);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	char		*news;
	char		*scan;
	unsigned int	sep_size;

	if (size == 0)
		return ((char *) malloc(sizeof(char)));
	sep_size = str_size(sep);
	news = (char *) malloc(sizeof(char) * final_size(size, strs, sep_size));
	if (!news)
		return (NULL);
	scan = news;
	i = 0;
	while (i < size)
	{
		scan = place_str(scan, strs[i]);
		if (i != size - 1)
			scan = place_str(scan, sep);
		i++;
	}
	*scan = '\0';
	return (news);
}
