/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hece <hece@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:32:10 by hece              #+#    #+#             */
/*   Updated: 2023/05/26 20:32:11 by hece             ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static inline void
	ft_atof_init(t_atof_param *t)
{
	t->iter = 0;
	t->dop = 1;
	t->result = 0;
	t->fraction = 0;
	t->fraction_count = 1;
}

float
	ft_atof(const char *str)
{
	t_atof_param	t;

	t.iter = 0;
	ft_atof_init(&t);
	while ((str[t.iter] >= '\t' && str[t.iter] <= '\r') || str[t.iter] == ' ')
		t.iter++;
	if (str[t.iter] == '+' || str[t.iter] == '-')
	{
		if (str[t.iter++] == '-')
			t.dop *= -1;
	}
	while (str[t.iter] >= '0' && str[t.iter] <= '9' && str[t.iter] != '\0')
		t.result = ((str[t.iter++] - '0') + (t.result * 10));
	if (str[t.iter] == '.')
		t.iter++;
	while (str[t.iter] >= '0' && str[t.iter] <= '9' && str[t.iter] != '\0')
	{
		t.fraction = t.fraction + (str[t.iter++] - '0')
			/ (float) ft_pow(10, t.fraction_count);
		t.fraction_count++;
	}
	return (t.dop * (t.result + t.fraction));
}

double
	ft_pow(double base, int exponent)
{
	double	result;
	int		count;
	int		exponent_positive;
	double	one;

	result = 1.0;
	count = 0;
	exponent_positive = exponent;
	one = 1.0;
	if (exponent < 0)
		exponent_positive = -exponent;
	while (count < exponent_positive)
	{
		result *= base;
		count++;
	}
	if (exponent < 0)
		result = one / result;
	return (result);
}

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
