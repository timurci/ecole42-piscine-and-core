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
	new_list->arr = (int *) malloc(sizeof(int) * new_list->inv);
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
