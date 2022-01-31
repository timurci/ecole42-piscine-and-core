/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:40:39 by tcakmako          #+#    #+#             */
/*   Updated: 2022/01/31 15:55:03 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*strrchr(const char *s, int c)
{
	char	*intl;

	intl = s;
	while (*s)
		s++;
	while (!(s == intl))
	{
		if (*s == (unsigned char) c)
			return (s);
		s--;
	}
	if (*s == (unsigned char) c)
		return (s);
	return (NULL);
}
