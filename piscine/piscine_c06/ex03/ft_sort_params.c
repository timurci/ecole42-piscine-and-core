/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:38:23 by tcakmako          #+#    #+#             */
/*   Updated: 2021/12/09 13:16:54 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

int	cmp(char *s1, char *s2)
{
	unsigned int	index;
	unsigned char	c1;
	unsigned char	c2;

	index = 0;
	while (s1[index] != '\0' || s2[index] != '\0')
	{
		c1 = s1[index];
		c2 = s2[index];
		if (c1 != c2)
			return (c1 - c2);
		index++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	i;
	int	hold;
	int	written;
	int	prev;

	hold = 1;
	written = 0;
	prev = 0;
	while (written < ac - 1)
	{
		i = 1;
		while (i < ac)
		{
			if (hold == prev && cmp(av[i], av[prev]) > 0)
				hold = i;
			else if (cmp(av[hold], av[i]) > 0 && cmp(av[i], av[prev]) > 0)
				hold = i;
			i++;
		}
		prev = hold;
		write(1, av[hold], ft_strlen(av[hold]));
		written++;
	}	
	return (0);
}
