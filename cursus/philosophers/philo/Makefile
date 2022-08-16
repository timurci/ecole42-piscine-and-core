CC=cc
CFLAGS=-Wall -Wextra -Werror
SRCS=$(wildcard *.c)
OBJS=$(SRC:%.c=.o)
LIBFLAGS=-I ft_printf -L ft_printf -l ftprintf
NAME=philo

all: $(NAME)

$(NAME): ft_printf $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ -c $^

ft_printf:
	make -C ft_printf
clean:
	rm -rf $(OBJS)
	make -C ft_printf clean
fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
	make -C ft_printf fclean
re: fclean all

.PHONY: ft_printf clean fclean re
