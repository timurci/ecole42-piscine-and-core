#include "parse.h"

size_t
	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char
	*ft_strdup(const char *str)
{
	char	*string;
	size_t	index;

	string = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (string == NULL)
		return (NULL);
	index = 0;
	while (str[index] != '\0')
	{
		string[index] = str[index];
		index++;
	}
	string[index] = '\0';
	return (string);
}	
