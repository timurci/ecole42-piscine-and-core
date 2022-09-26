/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:04 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/08 14:57:54 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// example : *s = ",,hello,,,world,," c = ','

static size_t	cword(char const *s, char c)
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

static char	*wgrab(char **strs, char const *s, char c)
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

static void	freelist(char ***strs, size_t *loop_element, size_t max)
{
	char	**scan;

	scan = *strs;
	while (*scan)
		free(*(scan++));
	free(*strs);
	*strs = NULL;
	*loop_element = max;
}

char	**ft_split(char const *str, char c)
{
	size_t	w_count;
	size_t	wscan;
	char	**strs;
	char	*s;

	if (!str)
		return (NULL);
	s = (char *) str;
	w_count = cword(s, c);
	strs = (char **) ft_calloc(1, sizeof(char *) * (w_count + 1));
	if (!strs)
		return (NULL);
	wscan = 0;
	while (wscan++ < w_count)
	{
		while (*s && *s == c)
			s++;
		s = wgrab(&strs[wscan - 1], s, c);
		if (!s)
			freelist(&strs, &wscan, w_count);
	}
	return (strs);
}
