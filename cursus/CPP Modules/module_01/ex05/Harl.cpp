/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:05:09 by tcakmako          #+#    #+#             */
/*   Updated: 2022/11/28 13:37:17 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(void)
{
	fmap[0].name = "DEBUG";
	fmap[0].fptr = &Harl::debug;
	fmap[1].name = "INFO";
	fmap[1].fptr = &Harl::info;
	fmap[2].name = "WARNING";
	fmap[2].fptr = &Harl::warning;
	fmap[3].name = "ERROR";
	fmap[3].fptr = &Harl::error;
}

void	Harl::debug(void)
{
	std::cout << "You called me to DEBUG" << std::endl;
}

void	Harl::info(void)
{
	std::cout << "You called me for INFO" << std::endl;
}

void	Harl::warning(void)
{
	std::cout << "You called me for WARNING" << std::endl;
}

void	Harl::error(void)
{
	std::cout << "You called me for ERROR" << std::endl;
}

void	Harl::complain(std::string level)
{
	for (int i = 0; i < 4; i++)
		if (!fmap[i].name.compare(level))
		{
			(this->*(fmap[i].fptr))();
			break ;
		}
}
