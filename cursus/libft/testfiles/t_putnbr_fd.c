#include <stdio.h>
#include "../libfiles/libft.h"

int	main(void)
{
	ft_putnbr_fd(52783, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-52783, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(0, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-2147483648, 1);
	write(1, "\n", 1);
	return (0);
}
