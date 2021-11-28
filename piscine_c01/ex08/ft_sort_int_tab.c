void	locate_min(int *tab, int tab_size, int min_index, int *holder)
{
	int	index;

	index = min_index;
	while (index < tab_size)
	{
		if(++index < tab_size && tab[index] < holder[0])
		{
			holder[0] = tab[index];
			holder[1] = index;
		}
	}
}

void	swap_min(int *tab, int tab_size, int min_index, int *holder)
{
	int	index;

	index = min_index;
	while (index < tab_size)
	{
		if (holder[0] < tab[index])
		{
			tab[holder[1]] = tab[index];
			tab[index] = holder[0];
			min_index++;
			break;
		}
		index++;
	}
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	min_index;
	int	index;
	int	min_holder[2];

	min_index = 0;
	index = 0;
	while (index < size)
	{
		min_holder[0] = 2147483647;
		locate_min(tab, size, min_index, min_holder);
		swap_min(tab, size, min_index, min_holder);
		index = min_index;
	}
}
