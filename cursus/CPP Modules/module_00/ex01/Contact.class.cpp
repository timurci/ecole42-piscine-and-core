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
