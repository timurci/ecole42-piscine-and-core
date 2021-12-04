int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	while (str[size] != 0)
		size++;
	return (size);
}		
