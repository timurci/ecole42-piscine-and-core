CC=cc
CFLAGS=-Wall -Wextra -Werror -I ft_printf/includes
NAME=push_swap
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): ft_printf $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L ft_printf/ -l ftprintf

ft_printf:
	make -C ft_printf/

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%errors.o:%errors.c
	$(CC) $(CFLAGS) -o $@ -c $^ -L ft_printf/ -l ftprintf

%errors.o:%errors.c
	$(CC) $(CFLAGS) -o $@ -c $^ -L ft_printf/ -l ftprintf

clean:
	rm -rf $(OBJS)
	make -C ft_printf/ clean

fclean: clean
	rm -rf $(NAME)
	make -C ft_printf/ fclean

print:
	echo $(SRCS)
	echo $(OBJS)

re: fclean all

.PHONY: all ft_printf clean fclean print re
