CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98
SRC=main.cpp Contact.class.cpp Phonebook.class.cpp
NAME=phonebook

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
