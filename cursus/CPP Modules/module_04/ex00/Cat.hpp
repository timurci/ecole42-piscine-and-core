#ifndef CAT_HPP
# define CAT_HPP

# include <string>
# include <iostream>
# include "Animal.hpp"

class	Cat : public Animal
{
	protected:
		std::string type;

	public:
		Cat(void);
		Cat(const Cat &);
		~Cat(void);

		Cat	&operator=(const Cat &);
		void	makeSound(void) const;
};

#endif
