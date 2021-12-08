int	ft_fibonacci(int index)
{
	int	sum;

	if (index < 0)
		return (-1);
	sum = 0;
	if (index > 1)
		sum = ft_fibonacci(index - 1) + ft_fibonacci(index - 2);
	if (index == 1)
		sum += 1;
	return (sum);
}
