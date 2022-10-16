/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:14:20 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/14 23:14:21 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#ifndef HORDE_SIZE
# define HORDE_SIZE 5
#endif

Zombie	*zombieHorde(int N, std::string name);

void	announceAll(Zombie *zombies, int N)
{
	for (int i = 0; i < N; i++)
		zombies[i].announce();
}

int	main(void)
{
	Zombie	*horde = NULL;

	horde = zombieHorde(HORDE_SIZE, "Zombi");
	announceAll(horde, HORDE_SIZE);
	if (horde)
		delete[] horde;
	return (0);
}
