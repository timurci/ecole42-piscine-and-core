CC=cc
CFLAGS=-Wall -Wextra -Werror -I libft
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
LIBFT=-L libft -l ft
READLINE=-l readline
NAME=minishell

all: $(NAME)

$(NAME): libft $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $^

#$(NAME): libft $(OBJS)
#	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)
#
#%.o:%.c
#	$(CC) $(CFLAGS) -o $@ -c $^ $(LIBFT) $(READLINE)

libft:
	make -C libft

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean:
	rm -rf $(OBJS) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all libft clean fclean re
