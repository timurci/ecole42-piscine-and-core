#ifndef COMMANDS_HPP
#define COMMANDS_HPP

# include "Irc.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define VALID_LEN 18

typedef struct s_cmd_info
{
	std::string	prefix;
	std::string	command;
	std::string	params;
}	t_cmd_info;

std::string	getListOfMembers(Channel &channel, const bool client_in_channel);
std::string	getSymbol(Channel &channel);
std::string	getChannelName(std::string msg_to_parse);
std::string	findNickname(std::string msg_to_parse);
//std::string	getReason(std::string msg_to_parse);

// #######################
// ###### COMMANDS #######
// #######################

void	nick(Client &client, const t_cmd_info &cmd_info, const std::map<const int, Client> &client_list);
int		pass(Client &client, const t_cmd_info &cmd_info, const std::string &server_password);
void	user(Client &client, const t_cmd_info &cmd_info);
int		ping(Client &client, const t_cmd_info &cmd_info);
void	quit(Client &client, const t_cmd_info &cmd_info, std::map<std::string, Channel> &channel_list);
void	join(Client &client, const t_cmd_info &cmd_info, std::map<std::string, Channel> &channel_list); // revise the algorithm
void	privmsg(Client &client, const t_cmd_info &cmd_info, std::map<const int, Client> &client_list,
			std::map<std::string, Channel> &channel_list);
//void	notice(Client &client, const t_cmd_info &cmd_info, std::map<const int, Client> &client_list,
//			std::map<std::string, Channel> &channel_list);
void	modeFunction(Client &client, const t_cmd_info &cmd_info,
			std::map<const int, Client> &client_list, std::map<std::string, Channel> &channel_list);
void	names(Client &client, const t_cmd_info &cmd_info, std::map<std::string, Channel> &channel_list);
void	bot(Client &client, const std::string &bot_cmd);
void	invite(Client &client, const t_cmd_info &cmd_info, std::map<const int, Client> &client_list,
			std::map<std::string, Channel> &channel_list);
void	kick(Client &client, const t_cmd_info &cmd_info, std::map<std::string, Channel> &channel_list);
void	motd(Client &client, const t_cmd_info &cmd_info);
void	part(Client &client, const t_cmd_info &cmd_info,
		  std::map<std::string, Channel> &channel_list);
void 	oper(Client &client, const t_cmd_info &cmd_info,
		  const std::vector<t_server_op> &irc_op_list);
void	kill(Client &client, const t_cmd_info &cmd_info,
			std::map<const int, Client> &client_list,
			const std::vector<t_server_op> &irc_op_list);
void	list(Client &client, const t_cmd_info &cmd_info,
		  std::map<std::string, Channel> &channel_list);
void	topic(Client &client, const t_cmd_info &cmd_info,
		   std::map<std::string, Channel> &channel_list);

// CHANNEL MODES

typedef struct s_mode_info
{
	std::string	target;
	std::string	mode;
	std::string	params;
}	t_mode_info;

void    banChannelMode(Client &client, const std::string &mode_params, Channel &channel, const std::string &mode_str);
void	keyChannelMode(Client &client, const std::string &mode_params, Channel &channel, const std::string &mode_str);
void	limitChannelMode(Client &client, const std::string &mode_params, Channel &channel, const std::string &mode_str);
void	moderateChannelMode(Client &client, const std::string &mode_params, Channel &channel, const std::string &mode_str);
void	operatorChannelMode(Client &client, const std::string &mode_params, Channel &channel, const std::string &mode_str);
void	privateChannelMode(Client &client, const std::string &mode_params, Channel &channel, const std::string &mode_str);
void	secretChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode_str);
void	topicChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode_str);
void	voiceChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode_str);

#endif
