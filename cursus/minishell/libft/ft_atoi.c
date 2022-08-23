/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:08:23 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/23 15:54:15 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		result;
	char	is_neg;

	while (*str && ((*str > 8 && *str < 14) || *str == ' '))
		str++;
	if (!ft_strcmp("-2147483648", str))
		return (-2147483648);
	result = 0;
	is_neg = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		is_neg *= -1;
		str++;
	}
	while (*str && (*str > 47 && *str < 58))
		result = result * 10 + (*(str++) - 48);
	return (result * is_neg);
}
