int	ft_iterative_power(int nb, int power)
{
	int	product;

	if (power == 0)
		return (1);
	product = 1;
	while (power > 0)
	{
		product *= nb;
		power--;
	}
	return (product);
}
