#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void)
{
	std::cout << "ScavTrap default constructor called" << std::endl;
	hp = 100;
	std::cout << "ClapTrap HP is set to " << hp << std::endl;
	ep = 50;
	ad = 20;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
	std::cout << "ScavTrap string constructor called" << std::endl;
	hp = 100;
	ep = 50;
	ad = 20;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap destructor called" << std::endl;
}

ScavTrap	&ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << "ScavTrap assignment operator called" << std::endl;
	hp = other.hp;
	ep = other.ep;
	ad = other.ad;
	return (*this);
}

void	ScavTrap::attack(const std::string &target)
{
	if (hp <= 0)
	{
		std::cout << "ScavTrap " << name
					<< " is broken, it cannot attack!" << std::endl;
		return ;
	}
	if (ep <= 0)
	{
		std::cout << "ScavTrap " << name
					<< " has no energy left, it cannot attack!" << std::endl;
		return ;
	}
	std::cout << "ScavTrap charges to target " << target << std::endl;
	ep--;
}

void	ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << name << " is in gate keeper mode" << std::endl;
}
