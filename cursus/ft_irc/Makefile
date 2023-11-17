CC=c++
CFLAGS=-Wall -Wextra -Werror --std=c++98 -I include
NAME=ft_irc
SRC=\
	src/main.cpp src/utils.cpp \
	src/server/Server.cpp src/server/parsing.cpp \
	src/server/ManageServer.cpp src/server/ManageServerUtils.cpp \
	src/client/Client.cpp \
	src/commands/nick.cpp src/commands/user.cpp src/commands/pass.cpp \
	src/commands/ping.cpp src/commands/quit.cpp \
	src/channel/Channel.cpp \
	# src/commands/join.cpp src/commands/privmsg.cpp \
	# src/channel/...
OBJ_DIR=obj
OBJ=$(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ_DIR) :
	@mkdir -p $(sort $(dir $(OBJ))) \
	&& echo '======  Object dir added  ======'

$(OBJ) : $(OBJ_DIR)/%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

printobj:
	@echo $(OBJ)

printsrc:
	@echo $(SRC)

printobjdir:
	@echo $(sort $(dir $(OBJ)))

clean:
	@rm -f $(NAME) \
	&& echo '====== Executable removed ======'

fclean: clean
	@rm -rf $(OBJ_DIR) \
	&& echo '======  Objects removed   ======'

re: fclean all

.PHONY: all clean fclean re printobj printsrc
