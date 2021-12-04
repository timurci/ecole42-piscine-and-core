#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

char	check_base(char *base)
{
	int	index;
	char	*scan;

	index = 0;
	while (base[index] != 0)
	{
		if (base[index] == '+' || base[index] == '-')
			return (-1);
		scan = base;
		while (scan < &base[index])
		{
			if (*scan == base[index])
				return (-1);
			scan++;
		}
		index++;
		if (index > 16)
			return (-1);
	}
	return (index);
}

void	transform(int n, char b)
{
	if (n >= b)
	{
		transform(n / b, b);
		transform(n % b, b);
	}
	else
	{
		if(n < 10)
			ft_putchar(n + 48);
		else
			ft_putchar(n + 55);		
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	char	b;
	
	b = check_base(base);
	if (b > 1)
	{
		if (nbr < 0)
		{
			write(1, "-", 1);
			nbr *= -1;
		}
		transform(nbr, b);
	}
}
