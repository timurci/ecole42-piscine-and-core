CC=cc
CFLAGS=-Wall -Wextra -Werror
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
NAME=philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%print.o:%print.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ -c $^

clean:
	rm -rf $(OBJS)
fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
re: fclean all

.PHONY: clean fclean re
