#include <unistd.h>

void	form_addr(unsigned long p, char *ads)
{
	if (p > 16)
		form_addr(p / 16, ads + 1);
	*ads = "0123456789abcdef"[p % 16];
}

void	print_hexv(unsigned char *p, unsigned int max)
{
	int	i;

	i = 0;
	while (i < 16 && (unsigned int) i < max)
	{
		if (i % 2 == 0 && i != 0)
			write(1, " ", 1);
		write(1, &("0123456789abcdef"[(p[i] / 16) % 16]), 1);
		write(1, &("0123456789abcdef"[p[i] % 16]), 1);
		i++;
	}
	while (i < 16)
	{
		write(1, "  ", 2);
		if (i++ % 2 == 0)
			write(1, " ", 1);
	}
	write (1, " ", 1);
}

void	print_chrv(unsigned char *p, unsigned int max)
{
	int	i;

	i = 0;
	while (i < 16 && (unsigned int) i < max)
	{
		if (p[i] > 31 && p[i] < 127)
			write(1, &p[i], 1);
		i++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned char	*p;
	unsigned int	i;
	int				j;
	char			ads[16];

	p = addr;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < 16)
			ads[j++] = '0';
		form_addr((unsigned long) p, ads);
		while (j >= 0)
			write(1, &ads[j--], 1);
		write(1, ": ", 2);
		print_hexv(p, size - i);
		print_chrv(p, size - i);
		write(1, "\n", 1);
		p += 16;
		i += 16;
	}
	return (addr);
}
