CFLAGSZ=-Wall -Wextra -Werror -l m -l mlx -l ftprintf \
		-L opengl -L ft_printf -framework OpenGL -framework Appkit
CFLAGSS=-Wall -Wextra -Werror
CC=cc
PATH_INC=-I opengl -I ft_printf/includes -I include
FILES=main ft_strdup handlers win_operations draw_operations \
	  colors sign conditions circle mandelbrot julia put_axis menu
SRCS=$(addprefix src/, $(addsuffix .c, $(FILES)))
OBJS=$(addprefix obj/, $(addsuffix .o, $(FILES)))
NAME=fractol
all: $(NAME)

$(NAME): libs path_obj $(OBJS)
	$(CC) $(CFLAGSZ) $(PATH_INC) $(OBJS) -o $(NAME) 
path_obj:
	@mkdir -p obj
obj/%.o: src/%.c
	$(CC) $(CFLAGSS) $(PATH_INC) -c $^ -o $@
libs:
	@make -C opengl
	@make -C ft_printf
fclean: clean
	rm -rf fractol
clean: libclean
	rm -rf obj
libclean:
	make -C opengl fclean
	make -C ft_printf fclean
re: clean all
