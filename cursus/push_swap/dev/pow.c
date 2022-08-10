#include "push_swap.h"

int	ft_pow(int base, int power)
{
	if (power > 1)
		base *= ft_pow(base, power - 1);
	else if (!power)
		return (1);
	return (base);
}
