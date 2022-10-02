CC=cc
HEADERS=-I include -I libft
CFLAGS=-Wall -Wextra -Werror $(HEADERS) -g
LIBFT=-L libft -l ft
READLINE=-lreadline
#-L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
SRCS=$(wildcard lexer/*.c) $(wildcard expander/*.c) $(wildcard shell/*.c) \
	 $(wildcard parser/*.c) $(wildcard errors/*.c) $(wildcard executor/*.c) \
	 $(wildcard builtin/*.c)
OBJS=$(SRCS:.c=.o)
MAINOBJ=main.o
SRCTEST=$(wildcard test/*.c)
OBJTEST=$(SRCTEST:.c=.o)
NAME=minishell
TESTNAME=custom_test

all: $(NAME)

$(NAME): libft $(MAINOBJ) $(OBJS)
	$(CC) $(CFLAGS) signals/signals.c -o $@ $(OBJS) $(MAINOBJ) $(LIBFT) $(READLINE)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $^

lexer/%.o: lexer/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

parser/%.o: parser/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

shell/%.o: shell/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

expander/%.o: expander/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

errors/%.o: errors/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

test/%.o: test/%.c
	$(CC) $(CFLAGS) -o $@ -c $^
libft:
	make -C libft

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJTEST)
	rm -rf $(MAINOBJ)
	make -C libft clean

fclean:
	rm -rf $(OBJS)
	rm -rf $(OBJTEST)
	rm -rf $(MAINOBJ)
	rm -rf $(NAME)
	rm -rf $(TESTNAME)
	rm -rf 
	make -C libft fclean

re: fclean all

test: libft $(OBJTEST) $(OBJS)
	$(CC) $(CFLAGS) -o $(TESTNAME) $(OBJTEST) $(OBJS) $(LIBFT) $(READLINE)

.PHONY: all libft clean fclean re test
