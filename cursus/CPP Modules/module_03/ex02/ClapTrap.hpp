/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:56:24 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/19 17:27:04 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

# include <string>
# include <iostream>

class	ClapTrap
{
	protected:
		std::string		name;
		int				hp;
		int				ep;
		unsigned int	ad;
	
	public:
		ClapTrap(void);
		ClapTrap(const ClapTrap &);
		ClapTrap(const std::string &);
		~ClapTrap(void);
		
		ClapTrap	&operator=(const ClapTrap &);
		void		attack(const std::string &);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);
};

#endif
