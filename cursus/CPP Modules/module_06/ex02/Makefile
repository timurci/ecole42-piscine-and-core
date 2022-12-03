CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98 -g
SRC=$(wildcard *.cpp)
NAME=real
SIZE?=3

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) -D ARRAY_SIZE=$(SIZE) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
