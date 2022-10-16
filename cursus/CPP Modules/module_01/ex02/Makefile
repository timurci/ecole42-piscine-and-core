CC=c++
CFLAGS=-Wall -Wextra -Werror
SRC=main.cpp
NAME=hi_brain

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
