#ifndef DOG_HPP
# define DOG_HPP

# include <string>
# include <iostream>
# include "Animal.hpp"

class	Dog : public Animal
{
	public:
		Dog(void);
		Dog(const Dog &);
		~Dog(void);

		Dog	&operator=(const Dog &);
		void	makeSound(void) const;
};

#endif
