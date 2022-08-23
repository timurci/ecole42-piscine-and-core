CC=cc
CFLAGS=-Wall -Wextra -Werror -I ft_printf/includes
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
LIBFLAGS=-L ft_printf/ -l ftprintf
NAME=philo

all: $(NAME)

$(NAME): ftprintf $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%print.o:%print.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ -c $^

ftprintf:
	make -C ft_printf
clean:
	rm -rf $(OBJS)
	make -C ft_printf clean
fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
	make -C ft_printf fclean
re: fclean all

.PHONY: ftprintf clean fclean re
