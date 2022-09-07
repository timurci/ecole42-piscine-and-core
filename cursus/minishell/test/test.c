/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:34:29 by tcakmako          #+#    #+#             */
/*   Updated: 2022/09/07 11:34:30 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "lexer.h"

int	main(int ac, char **av)
{
	char	**strs;
	int		itr;

	if (ac != 2)
		return (1);
	strs = split_tokens(av[1]);
	itr = 0;
	while (strs[itr])
		printf("%s\n", strs[itr++]);
	free(strs);
	return (0);
}
