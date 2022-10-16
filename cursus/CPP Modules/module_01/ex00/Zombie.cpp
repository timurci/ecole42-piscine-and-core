/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:14:01 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/14 23:14:03 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name)
{
	this->name = name;
}

Zombie::~Zombie(void)
{
	std::cout << this->name << " has been destroyed." << std::endl;
}

void	Zombie::announce(void)
{
	std::cout << this->name << ":  BraiiiiiiinnnzzzZ..." << std::endl;
}
