CC=cc
CFLAGS=-Wall -Wextra -Werror -I ft_printf/includes
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
LIBFLAGS=-L ft_printf -l ftprintf
NAME=philo

all: $(NAME)

$(NAME): ft_printf $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%philo_states.o:%philo_states.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ -c $^
%routines.o:%routines.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ -c $^
%atoi.o:%atoi.c
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
