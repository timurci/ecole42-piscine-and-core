/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:04 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/02 15:28:59 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// example : *s = ",,hello,,,world,," c = ','

size_t	static	cword(char const *s, char c)
{
	char	is_word;
	size_t	w_count;

	is_word = 0;
	w_count = 0;
	while (*s)
	{
		if (*s != c && !is_word)
		{
			is_word = 1;
			w_count++;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (w_count);
}

char static	*wgrab(char **strs, char const *s, char c)
{
	size_t	ssize;
	char	*news;

	ssize = 0;
	while (s[ssize] && s[ssize] != c)
		ssize++;
	news = malloc(sizeof(char) * (ssize + 1));
	if (!news)
		return (NULL);
	ssize = 0;
	while (*s && *s != c)
		news[ssize++] = *(s++);
	news[ssize] = 0;
	*strs = news;
	return ((char *) s);
}

void static	freelist(char **strs)
{
	char	**scan;

	scan = strs;
	while (*scan)
		free(*(scan++));
	free(strs);
}

char	**ft_split(char const *str, char c)
{
	size_t	w_count;
	size_t	wscan;
	char	**strs;
	char	*s;

	s = (char *) str;
	w_count = cword(s, c);
	strs = (char **) ft_calloc(1, sizeof(char *) * (w_count + 1));
	if (!strs)
		return (NULL);
	wscan = 0;
	while (wscan < w_count)
	{
		while (*s && *s == c)
			s++;
		s = wgrab(&strs[wscan], s, c);
		if (!s)
		{
			freelist(strs);
			return (NULL);
		}
		wscan++;
	}
	return (strs);
}
