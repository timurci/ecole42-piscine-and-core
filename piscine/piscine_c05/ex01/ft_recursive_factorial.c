int	ft_recursive_factorial(int nb)
{
	int	product;
	
	product = 1;
	if (nb > 0)
		product = nb * ft_recursive_factorial(nb - 1);
	if (nb == 0)
		return (1);
	return (product);
}
