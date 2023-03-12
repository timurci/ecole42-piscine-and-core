OS=$(shell uname)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I include -g
#CFLAGS=-Wall -Wextra -I include -lm
XPATH_LINUX=minilibx-linux
XFLAGS_LINUX=-I$(XPATH_LINUX) -L$(XPATH_LINUX) -lmlx -lXext -lX11
XPATH_MACOS=minilibx-opengl
XFLAGS_MACOS=-I$(XPATH_MACOS) -L$(XPATH_MACOS) -lmlx -framework OpenGL -framework Appkit
SRC=mlx_core/mlx_core.c mlx_utils/mlx_utils.c mlx_utils/color.c mlx_hook/mlx_hook.c main.c \
	3D/vector3_utils.c 3D/ray3.c 3D/color3.c 3D/point3.c 3D/vector3.c \
	geo/object_parameters.c geo/object_sphere.c geo/object_camera.c geo/objects.c
OBJ_DIR=obj
OBJ=$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
NAME=miniRT

ifeq ($(OS), Linux)
	XPATH=$(XPATH_LINUX)
	XFLAGS=$(XFLAGS_LINUX)
else
	XPATH=$(XPATH_MACOS)
	XFLAGS=$(XFLAGS_MACOS)
endif

all: $(NAME)

$(NAME): libx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(XFLAGS)

libx:
	@make -C $(XPATH)

#Duplicate
$(OBJ_DIR)/vector3_utils.o:vector3_utils.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -lm -o $@ -c $< -I $(XPATH)

$(OBJ) : $(OBJ_DIR)/%.o:%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(XPATH)

clean:
	@make -C $(XPATH) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libx
