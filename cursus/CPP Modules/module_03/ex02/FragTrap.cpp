#include "FragTrap.hpp"

FragTrap::FragTrap(void)
{
	std::cout << "FragTrap default constructor called" << std::endl;
	hp = 100;
	std::cout << "ClapTrap HP is set to " << hp << std::endl;
	ep = 100;
	ad = 30;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other)
{
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
	std::cout << "FragTrap string constructor called" << std::endl;
	hp = 100;
	ep = 100;
	ad = 30;
}

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap	&FragTrap::operator=(const FragTrap &other)
{
	std::cout << "FragTrap assignment operator called" << std::endl;
	hp = other.hp;
	ep = other.ep;
	ad = other.ad;
	return (*this);
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << name << ": lets do high fives guys!" << std::endl;
}
