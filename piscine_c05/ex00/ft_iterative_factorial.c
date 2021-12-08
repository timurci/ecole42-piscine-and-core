int	ft_iterative_factorial(int nb)
{
	int	product;

	product = 1;
	while (nb > 0)
		product *= nb--;
	return (product);
}
