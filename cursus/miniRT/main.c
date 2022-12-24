#include "mlx.h"
#include <stdlib.h>

int	main(void)
{
	void	*init;

	init = mlx_init();
	if (!init)
		return (1);
	return (0);
}
