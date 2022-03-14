#include <limits.h>
#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

int	main(void)
{
	printf("%ld\n", LONG_MAX);
	printf("%x\n", LONG_MAX);
	ft_printf("%x\n", LONG_MAX);
}
