#include <stdio.h>
#include <ctype.h>

int	ft_isascii(int c);

int	main(void)
{
	char	x;

	x = 'a';
	printf("x:\t%c\n", x);
	printf("isascii:\t%d\n", isascii(x));
	printf("ft_isascii:\t%d\n", ft_isascii(x));
	x = '1';
	printf("x:\t%c\n", x);
	printf("isascii:\t%d\n", isascii(x));
	printf("ft_isascii:\t%d\n", ft_isascii(x));
	x = -1;
	printf("x:\t%d\n", x);
	printf("isascii:\t%d\n", isascii(x));
	printf("ft_isascii:\t%d\n", ft_isascii(x));
	return (0);
}
