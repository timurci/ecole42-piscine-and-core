#include "ft_printf.h"
#include  "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	void	*p;

	p = malloc(1);
	ft_printf("hello world!\n");
	ft_printf("%d\n", -53);
	ft_printf("%d\n", 0);
	ft_printf("%s\n", "lorem ipsum dolor sit amet.");
	ft_printf("%s\n", "lorem");
	ft_printf("%c\n", 'c');
	ft_printf("%u\n", 2147483648);
	ft_printf("%x\n", 15);
	ft_printf("%X\n", 15);
	ft_printf("%%\n");
	printf("---\n");
	ft_printf("%p\n", p);
	printf("---\n");
	printf("%p\n", p);
	printf("---\n");
	return (0);
}
