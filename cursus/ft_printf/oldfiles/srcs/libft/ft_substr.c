/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:49:59 by tcakmako          #+#    #+#             */
/*   Updated: 2022/02/18 12:23:29 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*news;
	size_t	scan;
	size_t	slen;

	if (!s || start >= ft_strlen(s) || !len || !ft_strlen(s))
		return (ft_strdup(""));
	scan = 0;
	slen = 0;
	while (s[slen + start] && slen < len)
		slen++;
	news = (char *) malloc(sizeof(char) * (slen + 1));
	if (!news)
		return (NULL);
	while (scan < slen)
	{
		news[scan] = s[scan + start];
		scan++;
	}
	news[scan] = 0;
	return (news);
}
