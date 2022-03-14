#include "ft_printf.h"
#include "libft.h"

int	main(void)
{
	ft_printf("%.5d\n", 2);
	ft_printf("%d\n", -5);
	ft_printf("%5d\n", -5);
	ft_printf("%4d\n", -1234);
}
