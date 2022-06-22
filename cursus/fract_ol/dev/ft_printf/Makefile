CC=cc
CFLAGS=-Wall -Wextra -Werror

PPATH=srcs/printf
LPATH=srcs/libft
SPATH=srcs
OPATH=objs

INCLUDE= -I ./includes

PSRCS=ft_printf.c ft_pformats.c dec_conv.c hex_conv.c ft_strcmp.c \
	  str_conv.c type1tokens.c fill.c ft_swaps.c sharp_type.c \
	  null_format.c
POBJS=$(PSRCS:.c=.o)

LSRCS=ft_strlen.c ft_strdup.c ft_isdigit.c ft_memcpy.c ft_calloc.c
LOBJS=$(LSRCS:.c=.o)

OBJS=$(foreach object, $(LOBJS) $(POBJS), $(addprefix $(OPATH)/, $(object)))

NAME=libftprintf.a
RM=rm -rf

all: $(NAME)

bonus: $(NAME)

$(NAME): obj_folder $(OBJS)
	ar rcs $(NAME) $(OBJS)
obj_folder:
	mkdir -p objs

$(OPATH)/%.o: $(PPATH)/%.c
	$(CC) $(INCLUDE) -c -o $@ $< $(CFLAGS)

$(OPATH)/%.o: $(LPATH)/%.c
	$(CC) $(INCLUDE) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) $(OBJS) objs
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all bonus clean fclean re obj_folder
