#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

# include <iostream>
# include <string>
# include "ClapTrap.hpp"

class	FragTrap: public ClapTrap
{
	public:
		FragTrap(void);
		FragTrap(const FragTrap &);
		FragTrap(const std::string &);
		~FragTrap(void);

		FragTrap	&operator=(const FragTrap &);
		void		highFivesGuys(void);
};

#endif
