/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_free_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:31:49 by hece              #+#    #+#             */
/*   Updated: 2023/05/26 20:31:50 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int
	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t		i;
	const char	*s1_lower;
	const char	*s2_lower;

	s1_lower = s1;
	s2_lower = s2;
	i = 0;
	while (i < size && (s1_lower[i] != '\0' || s2_lower[i] != '\0'))
	{
		if (s1_lower[i] != s2_lower[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void
	free_split(char **split)
{
	char	**ptr;

	if (split == NULL)
		return ;
	ptr = split;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(split);
}

void
	free_split_check_func(char **split)
{
	char	**ptr;

	if (split == NULL)
		return ;
	ptr = split;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
}

size_t
	ft_check_comma(char *split, char c)
{
	register int	index;
	register int	result;

	result = 0;
	index = 0;
	while (split[index] != '\0')
	{
		if (split[index] == c)
			result++;
		index++;
	}
	return (result);
}
