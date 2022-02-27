#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"
/*controls are not optimal due to norminette limitations.
 *ln14 check store && input
 *ln24 check store
 *
 */
int	ft_printf(const char *input, ...)
{
	va_list	ap;
	size_t	scan;
	size_t	mem;
	char	*store;

	va_start(input, ap);
	scan = 0;
	mem = 0;
	while (input[scan])
	{
		if (input[scan] == '%')
		{
			store = ft_strffjoin(store, ft_substr(input, mem, scan - mem));
			mem = pformat(input, scan, &store, ap);
			//if (mem < 0)
			//	return (check_cd(...));
			scan = mem;
			continue ;
		}
		scan++;
	}
	if (input[scan] == 0)
		store = ft_strffjoin(store, ft_substr(input, mem, scan - mem));
	va_end(ap);
	//return
}
