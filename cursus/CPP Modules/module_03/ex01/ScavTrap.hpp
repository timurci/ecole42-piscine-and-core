#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

# include <iostream>
# include <string>
# include "ClapTrap.hpp"

class	ScavTrap: public ClapTrap
{
	public:
		ScavTrap(void);
		ScavTrap(const ScavTrap &);
		ScavTrap(const std::string &);
		~ScavTrap(void);

		ScavTrap	&operator=(const ScavTrap &);
		void		attack(const std::string &);
};

#endif
