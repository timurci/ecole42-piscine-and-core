#include <stdio.h>
#include <ctype.h>

int	ft_isprint(int c);

int	main(void)
{
	char	x;

	x = 'a';
	printf("x:\t%c\n", x);
	printf("isprint:\t%d\n", isprint(x));
	printf("ft_isprint:\t%d\n", ft_isprint(x));
	x = '1';
	printf("x:\t%c\n", x);
	printf("isprint:\t%d\n", isprint(x));
	printf("ft_isprint:\t%d\n", ft_isprint(x));
	x = '\t';
	printf("x:\t%d\n", x);
	printf("isprint:\t%d\n", isprint(x));
	printf("ft_isprint:\t%d\n", ft_isprint(x));
	return (0);
}
