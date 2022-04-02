#include "push_swap.h"
#include <ctype.h> //replace for isdigit

static char	is_greater(char *s1, char *s2)
{
	while (*s2)
	{
		if (*s2 < *s1)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

int fatoi(char *s)
{
	size_t slen;

	slen = 0;
	while (s[slen] && slen < 11)
	{
		if (slen == 0 && (s[slen] == '-' || s[slen] == '+'))
			;
		else if (!isdigit(s[slen]))
			return (0);
		slen++;
	}
	if ((*s != '-' && slen > 10) || (slen == 11 && s[slen]))
		return (0);
	if ((slen == 11 && is_greater(s+1, "2147483648"))
		|| (*s != '-' && slen == 10 && is_greater(s, "2147483647")))
		return (0);
	return (atoi(s));
}
