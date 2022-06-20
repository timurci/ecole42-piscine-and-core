CFLAGS0=-Wall -Wextra -Werror -lm -framework OpenGL -framework Appkit
CFLAGS1=-Wall -Wextra -Werror
CC=cc
PATH_LIB=-L opengl -lmlx
PATH_INC=-I opengl
FILES=main ft_strdup handlers win_operations draw_operations \
	  colors sign conditions circle mandelbrot julia put_axis
SRCS=$(addprefix src/, $(addsuffix .c, $(FILES)))
OBJS=$(addprefix obj/, $(addsuffix .o, $(FILES)))
NAME=fractol
all: $(NAME)

$(NAME): minilib path_obj $(OBJS)
	$(CC) $(CFLAGS0) $(PATH_LIB) $(PATH_INC) $(OBJS) 
test:
	$(CC) $(CFLAGS1) src/ft_strdup.c $(PATH_LIB) $(PATH_INC) src/test.c
path_obj:
	mkdir -p obj
obj/%.o: src/%.c
	$(CC) $(CFLAGS1) $(PATH_LIB) $(PATH_INC) -c $^ -o $@
minilib:
	make -C opengl
fclean: clean
	rm -rf fractol
clean: miniclean
	rm -rf obj
miniclean:
	make -C opengl clean
re: clean all
