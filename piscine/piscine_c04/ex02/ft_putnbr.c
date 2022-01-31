#include <unistd.h>

unsigned int	get_size(int num)
{
	unsigned int	size;

	if (num == 0)
		return (1);

	size = 0;
	while (num > 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

unsigned int	ft_pow10(unsigned int pow)
{
	unsigned int	result;

	result = 1;
	while (pow > 0)
	{
		result *= 10;
		pow--;
	}
	return (result);
}

void	ft_putchr(int c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	unsigned int	size;

	if (nb == -2147483648)
		write(1, "-2147483648", 11);
	else if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	size = get_size(nb);
	while (size > 0)
	{
		ft_putchr(nb / ft_pow10(--size) % 10 + '0');
	}
	write(1, "\n", 1);
}
