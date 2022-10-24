/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:19:07 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/24 16:19:07 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.class.hpp"

Phonebook::Phonebook(void)
{
	this->filled = 0;
	this->last_index = 0;
}

Contact	Phonebook::get_contact(int index)
{
	return (this->contacts[index % 8]);
}

int	Phonebook::size(void)
{
	if (this->filled)
		return (8);
	else
		return (this->last_index);
}

void	Phonebook::add_contact(std::string f, std::string l,
								std::string n, std::string p,
								std::string s)
{
	this->contacts[this->last_index].set_fname(f);
	this->contacts[this->last_index].set_lname(l);
	this->contacts[this->last_index].set_nname(n);
	this->contacts[this->last_index].set_pnum(p);
	this->contacts[this->last_index].set_secret(s);

	this->last_index++;
	if (this->last_index > 7)
	{
		this->filled = 1;
		this->last_index = 0;
	}
}
