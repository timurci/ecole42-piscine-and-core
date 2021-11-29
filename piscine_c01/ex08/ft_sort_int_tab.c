void	ft_sort_int_tab(int *tab, int size)
{
	int	min_index;
	int	var_index;
	int	min_holder[2];

	min_index = 0;
	while (min_index < size)
	{
		var_index = min_index;
		min_holder[0] = 2147483647;
		while (var_index < size)
		{
			if (tab[var_index] < min_holder[0])
			{
				min_holder[0] = tab[var_index];
				min_holder[1] = var_index;
			}
			var_index++;
		}
		tab[min_holder[1]] = tab[min_index];
		tab[min_index] = min_holder[0];
		min_index++;
	}
}
