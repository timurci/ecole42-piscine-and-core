CC=c++
CFLAGLS=-Wall -Wextra -Werror -std=c++98
SRC=main.cpp Harl.cpp
NAME=harl

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
