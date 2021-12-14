#include <stdio.h>

char	*ft_strjoin(int s, char** strs, char* se);

int	main(void)
{
	char	*strs[] = {"bu bir", "yeni cümle", "olabilir mi?"};
	char	*sep = "--";
	int	size = 3;
	char	*news;

	news = ft_strjoin(size, strs, sep);
	printf("%s\n", news);
}
