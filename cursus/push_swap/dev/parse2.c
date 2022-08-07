/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:50:26 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/03 14:42:14 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	is_repeated(int *arr, size_t index)
{
	size_t	scan;

	scan = 0;
	while (scan < index)
		if (arr[scan++] == arr[index])
			return (1);
	return (0);
}

static void	control_arg(char *str, size_t index)
{
	unsigned int	itr;

	itr = 0;
	while (str[itr])
	{
		if (itr == 0 && (str[itr] == '+' || str[itr] == '-'))
			;
		else if ((str[itr] > 47 && str[itr] < 58))
			;
		else
			parsing_errors(1, &index);
		itr++;
	}
}

size_t	fill_array_with_args(t_ints *list, char **args)
{
	char	sign;
	size_t	itr;

	sign = 1;
	itr = 0;
	while (itr < list->inv)
	{
		control_arg(args[itr], itr);
		if (*(args[itr]) == '-')
			sign = -1;
		else if (*(args[itr]) > 47 && *(args[itr]) < 58)
			list->arr[itr] = parse_int(list, itr, *(args[itr]), &sign);
		else if (!*(args[itr]))
		{
			if (*(args[itr] - 1) > 47 && *(args[itr] - 1) < 58)
				list->arr[itr] *= sign;
			if (is_repeated(list->arr, itr++))
				return (itr);
			sign = 1;
			continue ;
		}
		if (itr < list->inv && *args[itr])
			args[itr]++;
	}
	return (-1);
}

size_t	fill_array(t_ints *list, char *str)
{
	char	sign;
	size_t	itr;

	sign = 1;
	itr = 0;
	while (itr < list->inv)
	{
		if (*str == '-')
			sign = -1;
		else if (*str > 47 && *str < 58)
			list->arr[itr] = parse_int(list, itr, *str, &sign);
		else if (*str == ' ' || !*str)
		{
			if (*(str - 1) > 47 && *(str - 1) < 58)
			{
				list->arr[itr] *= sign;
				if (is_repeated(list->arr, itr++))
					return (itr);
			}
			sign = 1;
		}
		if (*str)
			str++;
	}
	return (-1);
}

void	rev_array(t_ints *list)
{
	size_t	itr;
	int		tmp;

	itr = 0;
	while (itr < list->inv / 2)
	{
		tmp = list->arr[itr];
		list->arr[itr] = list->arr[list->inv - itr - 1];
		list->arr[list->inv - itr - 1] = tmp;
		itr++;
	}
}
