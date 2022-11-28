# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 13:37:16 by tcakmako          #+#    #+#              #
#    Updated: 2022/11/28 13:37:16 by tcakmako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98
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
