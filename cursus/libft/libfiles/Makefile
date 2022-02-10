CC=cc
CFLAGS=-Wall -Wextra -Werror -c
HEADER=libft.h
CFILES= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memcmp.c \
		ft_memmove.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJS=$(CFILES:.c=.o)
BONUS_CFILES= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			  ft_lstmap.c
BONUS_OBJS=$(BONUS_CFILES:.c=_bonus.o)
NAME=libft.a
RM=rm -f

all: $(NAME)
bonus: $(NAME) $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)
$(NAME): $(OBJS)
	ar rcs $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^
re: fclean all
fclean: clean
	$(RM) $(NAME)
clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
.PHONY: all bonus clean fclean re
