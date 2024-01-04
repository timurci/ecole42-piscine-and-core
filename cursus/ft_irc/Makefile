CC=c++
CFLAGS=-Wall -Wextra -Werror --std=c++98 -I include
NAME=ft_irc
SRC=\
	src/main.cpp src/utils.cpp \
	src/server/Server.cpp src/server/parsing.cpp \
	src/server/ManageServer.cpp src/server/ManageServerUtils.cpp \
	src/client/Client.cpp \
	src/commands/nick.cpp src/commands/user.cpp src/commands/pass.cpp \
	src/commands/ping.cpp src/commands/quit.cpp src/commands/invite.cpp \
	src/channel/Channel.cpp \
	src/commands/join.cpp src/commands/privmsg.cpp src/commands/names.cpp \
	src/commands/mode.cpp src/commands/kick.cpp src/commands/motd.cpp \
	src/commands/part.cpp src/commands/kill.cpp src/commands/list.cpp \
	src/commands/topic.cpp src/commands/oper.cpp src/commands/bot.cpp \
	src/commands/channel_modes/ban.cpp \
	src/commands/channel_modes/key.cpp \
	src/commands/channel_modes/limit.cpp \
	src/commands/channel_modes/moderate.cpp \
	src/commands/channel_modes/operator.cpp \
	src/commands/channel_modes/private.cpp \
	src/commands/channel_modes/secret.cpp \
	src/commands/channel_modes/topic.cpp \
	#src/commands/channel_modes/voice.cpp \
	#src/commands/notice.cpp
	# src/channel/...
OBJ_DIR=obj
OBJ=$(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))

OS=$(shell uname)

RED=\033[1;31m
GRN=\033[1;32m
RST=\033[0m

ifeq ($(OS), Linux)
	MSG=echo -e
else
	MSG=echo
endif

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) \
		&& $(MSG) '======      $(GRN)Compilation successful$(RST)     ======' \
		|| $(MSG) '======  $(RED)Compilation encountered error$(RST)  ======'

$(OBJ_DIR) :
	@mkdir -p $(sort $(dir $(OBJ))) \
	&& $(MSG) '======        $(GRN)Object dir added$(RST)        ======'

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
	&& $(MSG) '======       $(GRN)Executable removed$(RST)       ======'

fclean: clean
	@rm -rf $(OBJ_DIR) \
	&& $(MSG) '======        $(GRN)Objects removed$(RST)         ======' \
	|| $(MST) '======      $(GRN)Objects not removed$(RST)       ======'

re: fclean all

.PHONY: all clean fclean re printobj printsrc
