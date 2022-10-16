CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98
SRC=main.cpp Zombie.cpp newZombie.cpp randomChump.cpp
NAME=BraiiiiiiinnnzzzZ

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
