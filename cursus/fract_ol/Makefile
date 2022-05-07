CFLAGS=-Wall -Wextra -Werror -g -lm -framework OpenGL -framework Appkit -o $(NAME)
CC=cc
PATH_LIB=-L opengl -lmlx
PATH_INC=-I mlx
EXTRAS=ft_strdup.c
NAME=fractol
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(EXTRAS) $(PATH_LIB) $(PATH_INC) main.c
test: $(OBJS)
	$(CC) $(CFLAGS) $(EXTRAS) $(PATH_LIB) $(PATH_INC) test.c
clean:
	rm -rf fractol
re: clean all
