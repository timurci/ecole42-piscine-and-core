/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_isalpha.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:06:44 by tcakmako          #+#    #+#             */
/*   Updated: 2022/01/31 12:06:45 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isalpha(int c);

int	main(void)
{
	char	x;

	x = 'a';
	printf("x:\t%c\n", x);
	printf("isalpha:\t%d\n", isalpha(x));
	printf("ft_isalpha:\t%d\n", ft_isalpha(x));
	x = '1';
	printf("x:\t%c\n", x);
	printf("isalpha:\t%d\n", isalpha(x));
	printf("ft_isalpha:\t%d\n", ft_isalpha(x));
	x = -1;
	printf("x:\t%d\n", x);
	printf("isalpha:\t%d\n", isalpha(x));
	printf("ft_isalpha:\t%d\n", ft_isalpha(x));
	return (0);
}
