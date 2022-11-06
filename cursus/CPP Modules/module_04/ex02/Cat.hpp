#ifndef CAT_HPP
# define CAT_HPP

# include <string>
# include <iostream>
# include "Animal.hpp"
# include "Brain.hpp"

class	Cat : public Animal
{
	private:
		Brain	*brain;
	public:
		Cat(void);
		Cat(const Cat &);
		~Cat(void);

		Cat	&operator=(const Cat &);
		void	makeSound(void) const;
};

#endif
