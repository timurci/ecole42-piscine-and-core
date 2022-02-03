CC=cc
CFLAGS=-Wall -Wextra -Werror -c
CFILES= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memcmp.c \
		ft_memmove.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJS=$(CFILES:.c=.o)
NAME=libft.a
RM=rm -f

all: $(NAME)
	
$(NAME): $(OBJS)
	ar rcs $@ $^
$(OBJS): 
	$(CC) $(CFLAGS) $(CFILES)
re: fclean all
fclean: clean
	$(RM) $(LIB)
clean:
	$(RM) $(OBJS)
