/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:40:44 by tcakmako          #+#    #+#             */
/*   Updated: 2022/01/31 15:54:41 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char) c == *s)
			return (s);
		s++;
	}
	if (*s == (unsigned char) c)
		return (s);
	return (NULL);
}
