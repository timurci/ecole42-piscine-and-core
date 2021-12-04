#include <stdio.h>

char	check_base(char *b);

int	main(void)
{
	printf("%d\n", check_base("01")); 
	printf("%d\n", check_base("0123456789")); 
	printf("%d\n", check_base("0123456789ABCDEF")); 
	printf("%d\n", check_base("poneyvif")); 
	printf("%d\n", check_base("")); 
	printf("%d\n", check_base("0")); 
	printf("%d\n", check_base("001")); 
	return (0);
}
