int	ft_recursive_power(int nb, int power)
{
	int		product;

	product = 1;
	if (power > 0)
		product = nb * ft_recursive_power(nb, power - 1);
	return (product);
}
