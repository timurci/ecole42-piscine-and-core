#ifndef COMMANDS_HPP
#define COMMANDS_HPP

# include "Irc.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define VALID_LEN 17

typedef struct s_cmd_info
{
	std::string	prefix;
	std::string	command;
	std::string	params;
}	t_cmd_info;

std::string	getListOfMembers(std::string client, Channel &channel);
std::string	getChannelName(std::string msg_to_parse);
std::string	findNickname(std::string msg_to_parse);
std::string	getReason(std::string msg_to_parse);
std::string	getSymbol(Channel &channel);

// #######################
// ###### COMMANDS #######
// #######################

void	nick(Client &client, const t_cmd_info &cmd_info, const std::map<const int, Client> &client_list);
int		pass(Client &client, const t_cmd_info &cmd_info, const std::string &server_password);
void	user(Client &client, const t_cmd_info &cmd_info);
int		ping(Client &client, const t_cmd_info &cmd_info);
void	quit(Client &client, const t_cmd_info &cmd_info, std::map<std::string, Channel> &channel_list);
//void	join(Client &client, const t_cmd_info &cmd_info, std::map<std::string, Channel> &channel_list); // revise the algorithm
//void	privmsg(Client &client, const t_cmd_info &cmd_info);
//void	bot(Server *server, int const client_fd, std::map<const int, Client>::iterator it_client, std::string bot_cmd);
//void	invite(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	kick(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	kill(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	list(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	modeFunction(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	motd(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	names(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	notice(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	oper(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	part(Server *server, int const client_fd, cmd_struct cmd_infos);
//void	topic(Server *server, int const client_fd, cmd_struct cmd_infos);

// CHANNEL MODES

struct mode_struct
{
	std::string	target;
	std::string	mode;
	std::string	params;
};

//void	broadcastToAllChannelMembers(Server *server, Channel &channel, std::string reply);
//void    banChannelMode(Server *server, std::string datas[4], int const client_fd);
//void	keyChannelMode(Server *server, mode_struct mode_infos, int const client_fd, std::string mode_str);
//void	limitChannelMode(Server *server, std::string datas[4], int const client_fd);
//void	moderateChannelMode(Server *server, mode_struct mode_infos, int const client_fd, std::string mode_str);
//void	operatorChannelMode(Server *server, mode_struct mode_infos, int const client_fd, std::string str);
//void	privateChannelMode(Server *server, mode_struct mode_infos, int const client_fd, std::string mode_str);
//void	secretChannelMode(Server *server, mode_struct mode_infos, int const client_fd, std::string mode_str);
//void	topicChannelMode(Server *server, mode_struct mode_infos, int const client_fd, std::string mode_str);
//void	voiceChannelMode(Server *server, mode_struct mode_infos, int const client_fd, std::string str);

#endif
