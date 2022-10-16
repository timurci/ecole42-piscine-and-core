/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:17:30 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/14 23:17:31 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

class	Weapon
{
	private:
		std::string	type;

	public:
		Weapon(std::string t){this->type = t;}

		const std::string	&getType(void){return (this->type);}
		void				setType(std::string t){this->type = t;}
};

#endif
