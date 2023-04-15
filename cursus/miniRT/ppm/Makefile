OS=$(shell uname)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I include -lm -g
#CFLAGS=-Wall -Wextra -I include -lm
SRC=ppm/main.c \
	3D/vector3.c 3D/vector3_utils.c 3D/vector3_utils_extended.c 3D/ray3.c \
	3D/color3.c 3D/point3.c \
	geo/object_parameters.c geo/object_sphere.c geo/object_camera.c geo/objects.c \
	geo/object_light.c geo/object_plane.c \
	draw/draw_ppm.c \
	random/rand42.c
OBJ_DIR=obj
OBJ=$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
SAMPLING?=100
DEPTH?=50
PPM?=0
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
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) $(XFLAGS)

libx:
	@make -C $(XPATH)

#Duplicate
$(OBJ_DIR)/vector3_utils.o:vector3_utils.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -lm -o $@ -c $< -I $(XPATH)

$(OBJ) : $(OBJ_DIR)/%.o:%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -D SAMPLES_PER_PIXEL=$(SAMPLING) -D MAX_DEPTH=$(DEPTH) \
		-o $@ -c $< -I $(XPATH)

clean:
	@make -C $(XPATH) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libx
