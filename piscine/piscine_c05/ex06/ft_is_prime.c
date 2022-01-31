int	ft_is_prime(int nb)
{
	int	scanner;

	if (nb == 0 || nb == 1)
		return (0);
	scanner = 2;
	while (scanner <= nb / 2)
	{
		if (nb % scanner == 0)
			return (0);
		scanner++;
	}
	return (1);
}
