CC=cc
CFLAGS=-Wall -Wextra -Werror

PPATH=srcs/printf
LPATH=srcs/libft
SPATH=srcs
OPATH=objs

INCLUDE= -I ./includes

PSRCS=ft_printf.c ft_pformats.c ft_joins.c dec_conv.c hex_conv.c ft_strcmp.c \
	  str_conv.c
POBJS=$(PSRCS:.c=.o)

LSRCS=ft_strlen.c ft_substr.c ft_isdigit.c ft_strdup.c
LOBJS=$(LSRCS:.c=.o)

OBJS=$(foreach object, $(LOBJS) $(POBJS), $(addprefix $(OPATH)/, $(object)))

NAME=libftprintf.a
RM=rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OPATH)/%.o: $(PPATH)/%.c 
	$(CC) $(INCLUDE) -c -o $@ $< $(CFLAGS)

$(OPATH)/%.o: $(LPATH)/%.c
	$(CC) $(INCLUDE) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
