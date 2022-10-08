CC=cc
CFLAGS=-Wall -Wextra -Werror
PLIB=-I ft_printf/includes -L ft_printf -l ftprintf
all: client server
client:
	$(CC) $(CFLAGS) client.c ft_atoi.c -o client
server: print
	$(CC) $(CFLAGS) server.c -o server $(PLIB)
print:
	make -C ft_printf
clean:
	make -C ft_printf clean
fclean: 
	make -C ft_printf fclean
	rm -f client
	rm -f server
re: fclean all
