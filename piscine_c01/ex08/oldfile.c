void	ft_sort_int_tab(int *tab, int size)
{
	int	comp_part;
	int	comp_index;
	int	main_index;
	int	min_index;

	min_index = 0;
	main_index = min_index;
	//add master loop
	while (main_index < size)
	{
		if (main_index == 0)
		{
			comp_part = tab[main_index];
			comp_index = main_index;
		}
		else if (++main_index < size && comp_part > tab[main_index]) //incremented index
		{
			comp_part = tab[main_index];
			comp_index = main_index;
		}	
		main_index = min_index;
		while (main_index < size)
		{
			if(comp_part < tab[main_index])
			{
				tab[comp_index] = tab[main_index];
				tab[main_index] = comp_part;
				min_index = main_index;
			}
		}
	}
	//5612873 num 1 i 2
	//if 1 < 5 add 1 instead of 5, put 5 at pos 2
}
