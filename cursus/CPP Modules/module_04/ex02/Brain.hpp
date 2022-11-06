#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>
# include <iostream>

class	Brain
{
	private:
		std::string	ideas[100];

	public:
		Brain(void);
		Brain(const Brain &);
		~Brain(void);

		Brain	&operator=(const Brain &);
};

#endif
