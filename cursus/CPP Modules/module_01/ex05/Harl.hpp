/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:05:14 by tcakmako          #+#    #+#             */
/*   Updated: 2022/11/28 13:37:17 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_H
# define HARL_H

# include <iostream>
# include <string>

class	Harl
{
	private:
		typedef struct s_fmap
		{
			std::string	name;
			void		(Harl::*fptr)(void);
		}		t_fmap;

		void	debug(void);
		void	info(void);
		void	warning(void);
		void	error(void);

		t_fmap	fmap[4];

	public:
		Harl(void);
		void	complain(std::string level);
};

#endif
