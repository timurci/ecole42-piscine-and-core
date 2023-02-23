CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98
SRC=$(wildcard *.cpp)
NAME=convert

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
