OS=$(shell uname)
CC=cc
CFLAGS=-Wall -Wextra -Werror
XPATH_LINUX=minilibx-linux
XFLAGS_LINUX=-I$(XPATH_LINUX) -L$(XPATH_LINUX) -lmlx -lXext -lX11
SRC=main.c
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

$(OBJ) : $(OBJ_DIR)/%.o:%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(XFLAGS)

clean:
	@make -C $(XPATH) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libx
