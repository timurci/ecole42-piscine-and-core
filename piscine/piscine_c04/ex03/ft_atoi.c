char	*pass_wspace(char *s)
{
	while (*s != 0)
	{
		if (*s == ' ' || (*s > 8 && *s < 14))
			s++;
		else
			break ;
	}
	return (s);
}

int	transform(char *start, char *end, unsigned int neg_count)
{
	int	result;

	result = 0;
	while (start < end)
	{
		result = (result * 10) + (*start - 48);
		start++;
	}
	if (neg_count % 2 == 1)
		result *= -1;
	return (result);
}

int	ft_atoi(char *str)
{
	unsigned int	neg_sign;
	char		*starter;

	neg_sign = 0;
	starter = 0;
	str = pass_wspace(str);
	while (*str != 0)
	{
		if (starter == 0 && (*str == '-' || *str == '+'))
		{
			if(*str == '-')
				neg_sign++;
		}
		else if (!(*str >= '0' && *str <= '9'))
			break ;
		else if (starter == 0)
			starter = str;
		str++;
	}
	return (transform(starter, str, neg_sign));
}
