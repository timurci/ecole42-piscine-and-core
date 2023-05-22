OS=$(shell uname)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I include -g
#CFLAGS=-Wall -Wextra -I include -lm
SAMPLING?=100
DEPTH?=50
PPM?=0
ASPECT_RATIO?=1.777777777f
WIDTH?=800
XPATH_LINUX=minilibx-linux
XFLAGS_LINUX=-I$(XPATH_LINUX) -L$(XPATH_LINUX) -lmlx -lXext -lX11
XPATH_MACOS=minilibx-opengl
XFLAGS_MACOS=-I$(XPATH_MACOS) -L$(XPATH_MACOS) -lmlx -framework OpenGL -framework Appkit
SRC=3D/vector3.c 3D/vector3_utils.c 3D/vector3_utils_extended.c 3D/ray3.c \
	3D/color3.c 3D/point3.c \
	geo/object_parameters.c geo/object_sphere.c geo/object_camera.c geo/objects.c \
	geo/object_light.c geo/object_plane.c \
	geo/object_cylinder.c geo/object_cylinder_params.c \
	random/rand42.c \
	parse/ft_split.c parse/get_next_line.c parse/parse.c parse/utils.c
ifeq ($(PPM), 0)
	SRC+=main.c draw/draw_mlx.c mlx_core/mlx_core.c mlx_utils/mlx_utils.c \
		 mlx_utils/color.c mlx_hook/mlx_hook.c
else
	SRC+=ppm/main.c draw/draw_ppm.c mlx_utils/color.c
endif
OBJ_DIR=obj
OBJ=$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
NAME=miniRT

ifeq ($(OS), Linux)
		XPATH=$(XPATH_LINUX)
		XFLAGS=$(XFLAGS_LINUX)
		CFLAGS+=-lm
else
		XPATH=$(XPATH_MACOS)
		XFLAGS=$(XFLAGS_MACOS)
endif

ifeq ($(PPM), 0)
all: $(NAME)
else
all: $(NAME)_ppm
endif

$(NAME): libx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(XFLAGS)

$(NAME)_ppm: $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

libx:
	@make -C $(XPATH)

#Duplicate
$(OBJ_DIR)/vector3_utils.o:vector3_utils.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -lm -o $@ -c $< -I $(XPATH)

$(OBJ) : $(OBJ_DIR)/%.o:%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) \
		-D SAMPLES_PER_PIXEL=$(SAMPLING) -D MAX_DEPTH=$(DEPTH) \
		-D WIDTH=$(WIDTH) -D ASPECT_RATIO=$(ASPECT_RATIO) \
		-o $@ -c $< -I $(XPATH)

clean:
	@make -C $(XPATH) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	norminette include main.c 3D geo draw mlx_core mlx_utils mlx_hook random

norminette: norm

.PHONY: all clean fclean re libx norm norminette
