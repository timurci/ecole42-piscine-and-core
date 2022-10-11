#include <iostream>
#include <iomanip>
#include "Phonebook.class.hpp"
#include "Contact.class.hpp"

void	print_info(Contact c)
{
	std::cout << "First name   : " << c.get_fname() << std::endl;
	std::cout << "Last name    : " << c.get_lname() << std::endl;
	std::cout << "Nickname     : " << c.get_nname() << std::endl;
	std::cout << "Phone number : " << c.get_pnum() << std::endl;
	std::cout << "Dark secret  : " << c.get_secret() << std::endl;
}

std::string	get_input(const char *prompt)
{
	std::string	input;

	while (!input.compare(""))
	{
		std::cout << prompt;
		std::cin >> input;
	}
	return (input);
}

void	contact_add_prompt(Phonebook &pbook)
{
	std::string	info[5];

	info[0] = get_input("Enter first name   : ");
	info[1] = get_input("Enter last name    : ");
	info[2] = get_input("Enter nickname     : ");
	info[3] = get_input("Enter phone number : ");
	info[4] = get_input("Enter dark secret  : ");
	pbook.add_contact(info[0], info[1], info[2], info[3], info[4]);
}

void	contact_search_prompt(Phonebook &pbook)
{
	Contact	c;

	for (int i = 0; i < pbook.size(); i++)
	{
		c = pbook.get_contact(i);
		std::cout << std::setw(10) << i << '|';
		if (c.get_fname().size() > 10)
			std::cout << c.get_fname().substr(0, 9) << ".|";
		else
			std::cout << std::setw(10) << c.get_fname() << '|';
		if (c.get_lname().size() > 10)
			std::cout << c.get_lname().substr(0, 9) << ".|";
		else
			std::cout << std::setw(10) << c.get_lname() << '|';
		if (c.get_nname().size() > 10)
			std::cout << c.get_nname().substr(0, 9) << '.' << std::endl;
		else
			std::cout << std::setw(10) << c.get_nname() << std::endl;
	}

	int	search_index;

	std::cout << "Select an entry to view: ";
	std::cin >> search_index;
	if (search_index > pbook.size() - 1)
		std::cout << "Invalid index." << std::endl;
	else
		print_info(pbook.get_contact(search_index));
}

int	main(void)
{
	Phonebook	pbook;
	std::string	cmd;

	while (cmd.compare("EXIT"))
	{
		std::cout << "> ";
		std::cin >> cmd;
		if (!cmd.compare("ADD"))
			contact_add_prompt(pbook);
		else if (!cmd.compare("SEARCH"))
		{
			if (!pbook.size())
				std::cout << "No records." << std::endl;
			else
				contact_search_prompt(pbook);
		}
	}
	return (0);
}
