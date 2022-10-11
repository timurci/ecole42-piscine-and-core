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
		
		std::string	get_fname(void){return (first_name);}
		std::string	get_lname(void){return (last_name);}
		std::string	get_nname(void){return (nick_name);}
		std::string	get_pnum(void){return (phone_number);}
		std::string	get_secret(void){return (secret);}
};

#endif
