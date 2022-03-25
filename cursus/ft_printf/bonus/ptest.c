#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"

int	main(void)
{
	void	*p1;
	void	*p2;

	p1 = malloc(1);
	p2 = malloc(1);
	printf("%p %s %p\n", p1, "qwr", p2);
	ft_printf("%p %s %p\n", p1, "qwr", p2);
	return (0);
}
