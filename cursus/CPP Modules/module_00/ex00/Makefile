CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98
NAME=megaphone

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) megaphone.cpp -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean flcean re
