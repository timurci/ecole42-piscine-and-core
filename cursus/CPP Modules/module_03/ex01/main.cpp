/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:56:34 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/19 17:43:39 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap	ct("Bob");
	ScavTrap	ct2("Bob_V.2");

	for (int i = 0; i < 12; i++)
		ct2.attack("Bob");
	ct2.beRepaired(5);
	ct.beRepaired(5);
	ct.attack("Bob_V.2");
	ct.takeDamage(20);
	ct.beRepaired(100);
	ct.attack("Bob_V.2");

	return (0);
}
