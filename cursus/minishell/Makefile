CC=cc
HEADERS=-I include -I libft
CFLAGS=-Wall -Wextra -Werror $(HEADERS) -g
LIBFT=-L libft -l ft
READLINE=-l readline
#-lreadline
#-L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
SRCS=$(wildcard lexer/*.c) $(wildcard expander/*.c) $(wildcard shell/*.c) \
	 $(wildcard parser/*.c) $(wildcard errors/*.c) $(wildcard executor/*.c) \
	 $(wildcard builtin/*.c) $(wildcard signals/*.c)
OBJS=$(SRCS:.c=.o)
MAINOBJ=main.o
NAME=minishell

all: $(NAME)

$(NAME): libft $(MAINOBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MAINOBJ) $(LIBFT) $(READLINE)

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

signals/%.o: signals/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

libft:
	make -C libft

clean:
	rm -rf $(OBJS)
	rm -rf $(MAINOBJ)
	make -C libft clean

fclean:
	rm -rf $(OBJS)
	rm -rf $(MAINOBJ)
	rm -rf $(NAME)
	rm -rf 
	make -C libft fclean

re: fclean all

.PHONY: all libft clean fclean re
