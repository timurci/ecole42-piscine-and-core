#include <stdio.h>

int	main(void)
{
	printf("%8.4d\n", -8473);
	printf("%8.4d\n", 8473);
	printf("%8.5d\n", -8473);
	printf("%8.5d\n", 8473);
	printf("%3.7d\n", -8473);
	printf("%3.7d\n--------\n", 8473);
	printf("%03.7d\n", -8473);
	printf("%03.7d\n", 8473);
	printf("%5c\n", 'a');
}
