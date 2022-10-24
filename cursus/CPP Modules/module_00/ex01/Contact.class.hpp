/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:19:07 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/24 16:19:07 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP

# include <string>

class Contact
{
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nick_name;
		std::string	phone_number;
		std::string	secret;

	public:
		void		set_fname(std::string);
		void		set_lname(std::string);
		void		set_nname(std::string);
		void		set_pnum(std::string);
		void		set_secret(std::string);
		
		std::string	get_fname(void);
		std::string	get_lname(void);
		std::string	get_nname(void);
		std::string	get_pnum(void);
		std::string	get_secret(void);
};

#endif
