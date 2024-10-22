/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:56:34 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/28 18:48:55 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap	ct("Bob");
	ScavTrap	ct2("Bob_V.2");

	for (int i = 0; i < 51; i++)
		ct2.attack("Bob");
	ct2.beRepaired(5);
	ct.attack("Bob_V.2");
	ct2.takeDamage(500);
	ct2.beRepaired(100);
	ct2.guardGate();

	return (0);
}
