objects = ft_putchar.o ft_swap.o ft_putstr.o \
		  ft_strlen.o ft_strcmp.o
reqs = ft_putchar.c ft_swap.c ft_putstr.c \
	   ft_strlen.c ft_strcmp.c
all: $(objects)
	ar rcs libft.a $(objects)
$(objects): $(reqs)
	gcc -c -Wall -Wextra -Werror $(reqs)
fclean: clean
	rm libft.a
clean:
	rm $(objects)
