#include <stdlib.h>

int	ft_strcmp(char *s1, char *s2)
{
	while (*s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

int	count_word(char *str, char *sep, int sep_size)
{
	int	size;

	size = 0;
	while (*str)
	{
		if (*str == *sep && !ft_strcmp(str, sep))
		{
			str += sep_size;
			if (*str && ft_strcmp(str, sep))
				size++;
			continue ;
		}
		else if (size == 0)
			size++;
		str++;
	}
	return (size);
}

char	*add_str(char **strs, char *str, char *sep)
{
	int		size;
	char	*news;

	size = 0;
	while (str[size] && ft_strcmp(&str[size], sep))
		size++;
	news = (char *) malloc(sizeof(char) * (size + 1));
	*strs = news;
	while (size > 0)
	{
		*news = *str;
		news++;
		str++;
		size--;
	}
	*news = 0;
	return (str);
}

char	**ft_split(char *str, char *charset)
{
	int		sep_size;
	int		wc;
	char	**strs;

	sep_size = 0;
	while (charset[sep_size])
		sep_size++;
	wc = count_word(str, charset, sep_size);
	strs = (char **) malloc(sizeof(char *) * (wc + 1));
	wc = 0;
	while (*str)
	{
		if(*str == *charset && !ft_strcmp(str, charset))
			str += sep_size;
		else
		{
			str = add_str(&strs[wc], str, charset);
			wc++;
		}
	}
	strs[wc] = 0;
	return (strs);	
}
