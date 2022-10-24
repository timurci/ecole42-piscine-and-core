/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:56:27 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/16 20:56:42 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void)
{
	std::cout << "Default constructeor called" << std::endl;
	name = "CT00";
	hp = 10;
	ep = 10;
	ad = 0;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

ClapTrap::ClapTrap(const std::string &n)
{
	std::cout << "String constructor called" << std::endl;
	name = n;
	hp = 10;
	ep = 10;
	ad = 0;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "Destructor called" << std::endl;
}

ClapTrap	&ClapTrap::operator=(const ClapTrap &other)
{
	std::cout << "Assignment operator called" << std::endl;
	name = other.name;
	hp = other.hp;
	ep = other.ep;
	ad = other.ad;
	return (*this);
}

void	ClapTrap::attack(const std::string &target)
{
	if (hp <= 0)
	{
		std::cout << "ClapTrap " << name
					<< " is broken, it cannot attack!" << std::endl;
		return ;
	}
	if (ep <=  0)
	{
		std::cout << "ClapTrap " << name
					<< " has no energy left, it cannot attack!" << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << name << " attacks " << target
				<< ", causing " << ad << " points of damage!" << std::endl;
	ep--;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << name << " takes " << amount
				<< " amounts of damage!" << std::endl;
	hp -= amount;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (hp <= 0)
	{
		std::cout << "ClapTrap " << name
					<< " is broken, it cannot repair itself!"
					<< std::endl;
		return ;
	}
	if (ep <=  0)
	{
		std::cout << "ClapTrap " << name
					<< " has no energy left, it cannot repair itself!"
					<< std::endl;
		return ;
	}
	std::cout << "ClapTrap " << name << " repairs " << amount
				<< " amounts of damage!" << std::endl;
	hp += amount;
	ep--;
}
