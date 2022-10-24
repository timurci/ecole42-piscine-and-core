/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:19:07 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/24 16:19:07 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_CLASS_HPP
# define PHONEBOOK_CLASS_HPP

# include <string>
# include "Contact.class.hpp"

class	Phonebook
{
	private:
		Contact	contacts[8];
		bool	filled;
		int		last_index;

	public:
		Phonebook(void);

		Contact	get_contact(int index);
		int		size(void);
		void	add_contact(std::string f, std::string l,
							std::string n, std::string p,
							std::string s);
};

#endif
