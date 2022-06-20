/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:01:46 by tcakmako          #+#    #+#             */
/*   Updated: 2022/05/07 18:01:47 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *s)
{
	char	*news;
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	news = malloc(sizeof(*news) * (len + 1));
	if (!news)
		return (NULL);
	news[len] = 0;
	while (len-- > 0)
		news[len] = s[len];
	return (news);
}
