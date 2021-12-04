#include <unistd.h>

void	ft_putnbr_base(int nbr, char *base);

int	main(void)
{
	int	x;

	x = 1;

	ft_putnbr_base(x, "01");
	write(1, "\n", 1);
	ft_putnbr_base(x, "0123456789");
	write(1, "\n", 1);
	ft_putnbr_base(x, "0123456789ABCDEF");
	write(1, "\n", 1);
	ft_putnbr_base(x, "poneyvif");
	write(1, "\n", 1);
	return (0);
}
