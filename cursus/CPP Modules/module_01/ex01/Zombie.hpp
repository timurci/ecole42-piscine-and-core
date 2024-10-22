/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:14:42 by tcakmako          #+#    #+#             */
/*   Updated: 2022/11/28 13:37:15 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class	Zombie
{
	private:
		std::string	name;

	public:
		Zombie(void);
		~Zombie(void);

		void	set_name(std::string);

		void	announce(void);
};

#endif
