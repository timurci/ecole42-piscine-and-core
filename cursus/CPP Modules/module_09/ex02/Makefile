CC=c++
CFLAGS=-std=c++98 -Wall -Werror -Wextra
SRC=main.cpp #PmergeMe.cpp
NAME=PmergeMe

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -r $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
