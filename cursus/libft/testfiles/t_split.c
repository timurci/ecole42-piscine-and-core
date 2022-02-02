#include <stdio.h>

char	**ft_split(char const *s, char c);

int	main(void)
{
	char	**strs;
	char	*s = "---Hello---World!--hi!---";
	char	c = '-';

	strs = ft_split(s, c);
	while (*strs)
		printf("%s\n", *(strs++));
	return (0);
}
