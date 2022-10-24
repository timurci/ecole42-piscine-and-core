/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:19:07 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/24 16:19:07 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.class.hpp"

void	Contact::set_fname(std::string first_name)
{
	this->first_name = first_name;
}

void	Contact::set_lname(std::string last_name)
{
	this->last_name = last_name;
}

void	Contact::set_nname(std::string nick_name)
{
	this->nick_name = nick_name;
}

void	Contact::set_pnum(std::string phone_number)
{
	this->phone_number = phone_number;
}

void	Contact::set_secret(std::string secret)
{
	this->secret = secret;
}

std::string	Contact::get_fname(void)
{
	return (first_name);
}

std::string	Contact::get_lname(void)
{
	return (last_name);
}

std::string	Contact::get_nname(void)
{
	return (nick_name);
}

std::string	Contact::get_pnum(void)
{
	return (phone_number);
}

std::string	Contact::get_secret(void)
{
	return (secret);
}
