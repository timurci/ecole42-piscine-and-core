#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

void	print_types(const Animal *m, const Animal *j, const Animal *i)
{
	std::cout << "---\nObject\t" << "Type\n" << std::endl;
	std::cout << "meta\t" << m->getType() << std::endl;
	std::cout << "j \t" << j->getType() << std::endl;
	std::cout << "i \t" << i->getType() << std::endl;
}

void	print_sounds(const Animal *m, const Animal *j, const Animal *i)
{
	std::cout << "---\nObject\t" << "Sound\n" << std::endl;
	std::cout << "meta\t"; m->makeSound();
	std::cout << "j \t"; j->makeSound();
	std::cout << "i \t"; i->makeSound(); //will output the cat sound!
}

int	main(void)
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	print_types(meta, j, i);
	print_sounds(meta, j, i);
	std::cout << std::endl;
	delete meta;
	delete j;
	delete i;
	return (0);
}
