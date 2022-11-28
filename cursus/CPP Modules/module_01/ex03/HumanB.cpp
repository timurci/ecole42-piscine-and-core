/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:37:16 by tcakmako          #+#    #+#             */
/*   Updated: 2022/11/28 13:37:16 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */ /*                                                                            */ /*                                                        :::      ::::::::   */ /*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:16:52 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/14 23:16:53 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string n) : name(n), weapon(NULL)
{}

void	HumanB::attack(void)
{
	std::cout << name << " attacks with their " << weapon->getType();
	std::cout << std::endl;
}

void	HumanB::setWeapon(Weapon &w)
{weapon = &w;}
