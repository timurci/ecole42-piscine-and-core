CFLAGS=-Wall -Wextra -Werror -g -lm -framework OpenGL -framework Appkit -o $(NAME)
CC=cc
PATH_LIB=-L opengl -lmlx
PATH_INC=-I opengl
EXTRAS=ft_strdup.c handlers.c win_operations.c draw_operations.c colors.c \
	  sign.c conditions.c circle.c mandelbrot.c julia.c put_axis.c
NAME=fractol
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(EXTRAS) $(PATH_LIB) $(PATH_INC) main.c
test: $(OBJS)
	$(CC) $(CFLAGS) ft_strdup.c $(PATH_LIB) $(PATH_INC) test.c
clean:
	rm -rf fractol
re: clean all
