/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_isdigit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:06:50 by tcakmako          #+#    #+#             */
/*   Updated: 2022/01/31 12:06:52 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isdigit(int c);

int	main(void)
{
	char	x;

	x = 'a';
	printf("x:\t%c\n", x);
	printf("isdigit:\t%d\n", isdigit(x));
	printf("ft_isdigit:\t%d\n", ft_isdigit(x));
	x = '1';
	printf("x:\t%c\n", x);
	printf("isdigit:\t%d\n", isdigit(x));
	printf("ft_isdigit:\t%d\n", ft_isdigit(x));
	x = -1;
	printf("x:\t%d\n", x);
	printf("isdigit:\t%d\n", isdigit(x));
	printf("ft_isdigit:\t%d\n", ft_isdigit(x));
	return (0);
}
