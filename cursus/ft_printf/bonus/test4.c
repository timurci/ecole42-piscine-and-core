#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	printf("%p\n", -1);
	ft_printf("%p\n", -1);
	printf("%p\n", 1);
	ft_printf("%p\n", 1);
	printf("%p\n", LONG_MAX);
	ft_printf("%p\n", LONG_MAX);
	printf("%p\n", 0);
	ft_printf("%p\n", 0);




	return (0);
}
