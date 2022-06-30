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
			is_num = 0;
		else if (*str > 47 && *str < 58 && !is_num)
		{
			is_num = 1;
			inv++;
		}
		else if ((*str == '+' || *str == '-') && !sign)
			sign = 1;
		else if (*str < 48 || *str > 57)
			parsing_errors(1, &inv);
		str++;
	}
	return (inv);
}

static void	fill_array(t_ints *list, char *str)
{
	char	sign;
	size_t	itr;

	sign = 1;
	itr = 0;
	while (*str && itr < list->inv)
	{
		if (*str == '-')
			sign = -1;
		else if (*str > 47 && *str < 58)
			list->arr[itr] = list->arr[itr] * 10 + (*str - 48);
		else if (*str == ' ')
		{
			if (*(str - 1) > 47 && *(str - 1) < 58)
			{
				list->arr[itr] *= sign;
				itr++;
			}
			sign = 1;
		}
		str++;
	}
}

static void	rev_array(t_ints *list)
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

t_ints	*parse_args(char *str)
{
	t_ints	*new_list;

	new_list = (t_ints *) malloc(sizeof(*new_list));
	if (!new_list)
		return (NULL);
	new_list->inv = count_inv(str);
	new_list->max = new_list->inv;
	new_list->arr = (int *) malloc(sizeof(int) * new_list->inv);
	if (!new_list->arr)
		return (NULL);
	fill_array(new_list, str);
	rev_array(new_list);
	return (new_list);
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
