/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:16:43 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/14 23:16:44 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_A_HPP
# define HUMAN_A_HPP

# include "Weapon.hpp"
# include <string>
# include <iostream>

class	HumanA
{
	private:
		std::string	name;
		Weapon		&weapon;

	public:
		HumanA(std::string n, Weapon &w) : name(n), weapon(w){}

		void	attack(void);
};

#endif
