/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_isalnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:07:52 by tcakmako          #+#    #+#             */
/*   Updated: 2022/01/31 12:07:53 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isalnum(int c);

int	main(void)
{
	char	x;

	x = 'a';
	printf("x:\t%c\n", x);
	printf("isalnum:\t%d\n", isalnum(x));
	printf("ft_isalnum:\t%d\n", ft_isalnum(x));
	x = '1';
	printf("x:\t%c\n", x);
	printf("isalnum:\t%d\n", isalnum(x));
	printf("ft_isalnum:\t%d\n", ft_isalnum(x));
	x = -1;
	printf("x:\t%d\n", x);
	printf("isalnum:\t%d\n", isalnum(x));
	printf("ft_isalnum:\t%d\n", ft_isalnum(x));
	return (0);
}
