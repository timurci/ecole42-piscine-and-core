/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako tcakmako@student.42kocaeli.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:05:23 by tcakmako          #+#    #+#             */
/*   Updated: 2022/03/05 13:52:55 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char static	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	return (0);
}

char	ft_tkncmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	if (ft_isspace(*s1) || ft_isspace(*s2))
		return (0);
	return (*s1 - *s2);
}
