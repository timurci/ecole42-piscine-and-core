int	ft_printf(const char *x, ...);

int	main(void)
{
	ft_printf("*%8.4d*\n", -8473);
	ft_printf("*%8.4d*\n", 8473);
	ft_printf("*%8.5d*\n", -8473);
	ft_printf("*%8.5d*\n", 8473);
	ft_printf("*%3.7d*\n", -8473);
	ft_printf("*%3.7d*\n--------\n", 8473);
	ft_printf("*%03.7d*\n", -8473);
	ft_printf("*%03.7d*\n", 8473);
	ft_printf("*%5c*\n", 'a');
}
