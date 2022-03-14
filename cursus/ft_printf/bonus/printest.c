#include <stdio.h>

int	main(void)
{
	printf("---------\n");
	//printf("%#05x\n", 17);
	//printf("%#05.7x\n", 17);
	//printf("%#X\n", 17);
	printf("%+ 5d\n", 0);
	printf("%+05d\n", 17);
	printf("*%- 05.4d*\n", 17);
	printf("*% 05.7d*\n", 17);
	printf("*%-05d*\n", 17);
	printf("*%+-05d*\n", 17);
	printf("%0 05d\n", 17);
	printf("% 5.8d\n", 17);
	printf("% 5.1d\n", 17);
	printf("% 5.5d\n", 17);
	printf("%- 5.5d\n", 17);
	printf("% .012d\n", 17);
	printf("% 5d\n", 17);
	printf("%05.1d\n", 17);
	printf("% 05.8d\n", 17);
	printf("% 5d\n", 17);
	printf("% 5i\n", 17);
	printf("% 03.7i\n", 17);
	printf("% 05.7u\n", 17);
	//printf("%5s\n", "abc");
	//printf("% 5s\n", "abc");
	//printf("% 0 10s\n", "abc");
	return (0);
}
