int	ft_sqrt(int nb)
{
	int	n;

	if (nb == 1)
		return (1);
	n = 0;
	while (n < nb / 2)
	{
		if (n * n == nb)
			return (n);
		n++;
	}
	return (0);
}
