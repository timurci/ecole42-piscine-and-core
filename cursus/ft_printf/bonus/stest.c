#include <stdio.h>

int	main(void)
{
	char *s = "hello";

	printf("*%10s*\n", s);
	printf("*%-7.10s*\n", s);
	printf("*%-10s*\n", s);
	printf("*%-.10s*\n", s);
	printf("*%.010s*\n", s);
	return (0);
}
