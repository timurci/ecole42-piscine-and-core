/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:50:21 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/03 15:04:53 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	count_inv(char *str)
{
	size_t	inv;
	char	is_num;
	char	sign;

	inv = 0;
	is_num = 0;
	sign = 0;
	while (*str)
	{
		if (*str == ' ' && (!sign || (sign && is_num)))
		{
			is_num = 0;
			sign = 0;
		}
		else if (*str > 47 && *str < 58 && !(is_num++))
			inv++;
		else if ((*str == '+' || *str == '-') && !sign)
			sign = 1;
		else if (*str < 48 || *str > 57)
			parsing_errors(1, &(inv));
		str++;
	}
	return (inv);
}

t_ints	*parse_args(int argc, char **argv)
{
	t_ints	*new_list;
	size_t	return_checker;

	new_list = (t_ints *) malloc(sizeof(*new_list));
	if (argc > 2)
		new_list->inv = (size_t) argc - 1;
	else
		new_list->inv = count_inv(argv[1]);
	new_list->max = new_list->inv;
	new_list->arr = (int *) ft_calloc(1, sizeof(int) * new_list->inv);
	if (argc > 2)
		return_checker = fill_array_with_args(new_list, argv + 1);
	else
		return_checker = fill_array(new_list, argv[1]);
	if (return_checker != (size_t) -1)
	{
		delete_ints(new_list);
		parsing_errors(2, &return_checker);
	}
	rev_array(new_list);
	return (new_list);
}

int	parse_int(t_ints *list, size_t itr, unsigned char addition, char *sign)
{
	long	tmp;

	if (list->arr[itr] == -2147483648)
	{
		free(list->arr);
		free(list);
		parsing_errors(3, &itr);
	}
	tmp = (long) list->arr[itr] * 10 + (addition - 48);
	if (tmp == 2147483648 && *sign == -1)
	{
		tmp = -tmp;
		*sign = 1;
	}
	else if (tmp > 2147483647)
	{
		free(list->arr);
		free(list);
		parsing_errors(3, &itr);
	}
	return (tmp);
}

char	is_shift_sorted(t_ints *l)
{
	size_t	inx[2];
	size_t	scan;

	inx[0] = locate_index(l, min_element(l));
	inx[1] = locate_index(l, max_element(l));
	if ((inx[0] != l->inv - 1 && inx[0] + 1 != inx[1])
			|| (inx[0] == l->inv - 1 && inx[1] != 0))
		return (0);
	else 
	{
		scan = inx[0];
		while (scan - 1 != inx[1])
		{
			if (l->arr[scan] > l->arr[scan - 1])
				return (0);
			if (scan - 1 == 0)
			{
				if (l->arr[0] > l->arr[l->inv - 1])
					return (0);
				scan = l->inv;
			}
			scan--;
		}
	}
	return (1);
}

char	is_sorted(t_ints *list)
{
	size_t	itr;

	itr = 0;
	while (itr < list->inv - 1 && list->inv > 0)
	{
		if (list->arr[itr] < list->arr[itr + 1])
			return (0);
		itr++;
	}
	return (1);
}
